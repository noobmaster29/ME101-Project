//  July 19, 2018
//  Current working version
//  final working version in C?
//
//
//  main.c
//  TicTacToeC
//
//  Created on 6/26/18.
//  Copyright © 2018 Victor. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>

// maximum function
int total = 0;

struct move{
    int row;
    int column;
};

int maxx(int a,int b){
    if(a > b){
        return a;
    }
    return b;
}

// minx function

int minx(int a,int b){
    if(a < b){
        return a;
    }
    return b;
}

//Print board
void printBoard(char board[3][3]){
    printf("\n");
    for(int i = 0;i < 3; i++){
        //cout<<board[i][0]<<" | "<<board[i][1]<<" | "<<board[i][2]<<" \n"<<endl;
        printf(" %c | %c | %c\n",board[i][0],board[i][1],board[i][2]);

        if (i == 0 || i == 1){
            printf("---+---+---\n");
        }
    }
    //cout<<"\n\n\n";
    printf("\n");
}

// Evaluate Function or Validate Function
int evaluate(char board[3][3]){
    for(int i=0;i < 3;i++){
        if((board[i][0] != '_') && (board[i][0]==board[i][1]) && (board[i][2]==board[i][1])){
            if(board[i][0] == 'x'){
                return 10;
            }else if(board[i][0] =='o'){
                return -10;
            }
        }
    }
    for(int i=0;i < 3;i++){
        if((board[0][i] != '_') && (board[0][i]==board[1][i]) && (board[2][i]==board[1][i])){
            if(board[0][i] == 'x'){
                return 10;
            }else if(board[0][i] =='o'){
                return -10;
            }
        }
    }
    if((board[0][0] != '_') && (board[0][0]==board[1][1]) && (board[2][2]==board[1][1])){
        if(board[0][0] == 'x'){
            return 10;
        }else if(board[0][0] =='o'){
            return -10;
        }
    }
    if((board[0][2] != '_') && (board[0][2]==board[1][1]) && (board[2][0]==board[1][1])){
        if(board[0][2] == 'x'){
            return 10;
        }else if(board[0][2] =='o'){
            return -10;
        }
    }
    return 0;
}

// Function checking if any move left

int noMovesLeft(char board[3][3]){
    for(int i = 0;i < 3;i++){
        for(int j = 0;j < 3;j++){
            if(board[i][j] == '_'){
                return 0;
            }
        }
    }
    return 1;
}


// Minimax function for finding scores of each possible step
// Alpha Beta Pruned minMax function
int miniMax(char board[3][3],int depth, int isMax,int alpha,int beta){
    int score = evaluate(board);
    if(score == 10){
        return score - depth;
    }
    if(score == -10){
        return score + depth;
    }
    if(noMovesLeft(board) != 0){
        return 0;
    }
    if(isMax != 0){
        int bestVal = -1000;
        for(int i = 0; i < 3;i++){
            for(int j = 0;j < 3;j++){
                if(board[i][j] == '_'){
                    board[i][j] = 'x';
                    total += 1;
                    int val = miniMax(board,depth + 1 ,0,alpha,beta);
                    bestVal = maxx(bestVal,val);
                    alpha = maxx(bestVal,alpha);
                    //cout<<"In Max "<<bestVal<<endl;
                    //printBoard(board);
                    board[i][j] = '_';
                    if(beta <= alpha)
                        break;
                }
                if(beta <= alpha)
                    break;
            }
        }
        return bestVal;
    }else{
        int bestVal = 1000;
        for(int i = 0; i < 3;i++){
            for(int j = 0;j < 3;j++){
                if(board[i][j] == '_'){
                    board[i][j] = 'o';
                    total += 1;
                    int val = miniMax(board,depth + 1 ,1,alpha,beta);
                    bestVal = minx(bestVal,val);
                    beta = minx(bestVal,beta);
                    //cout<<"In Min "<<bestVal<<endl;
                    //printBoard(board);
                    board[i][j] = '_';
                    if(beta <= alpha)
                        break;
                }
                if(beta <= alpha)
                    break;
            }
        }
        return bestVal;
    }

}

// Finds the Best Move
struct move findBestMove(char board[3][3],int row,int col){
    struct move moveType;
    moveType.row=0;
    moveType.column=0;
    int bestVal = -1000;
    int alpha = -1000;
    int beta = 1000;
    for(int i = 0;i < 3; i++){
        for(int j =0;j < 3;j++){
            if(board[i][j] == '_'){
                board[i][j] = 'x';
                total += 1;
                int moveVal = miniMax(board,0,0,alpha,beta);
                board[i][j] = '_';
                //cout <<i<<" "<<j<<" "<<moveVal<<endl;
                if(moveVal > bestVal){
                    moveType.row = i;
                    moveType.column = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    return moveType;
}


// game board
void gamePlay(char board[3][3]){
    for(int i =0 ;i < 3;i++){
        for(int j =0;j< 3;j++){
            board[i][j]='_';
        }
    }
    int move = 0;
    int row=0,col =0;
    printBoard(board);
    int counter = 0;
    printf("Go first(1) or second(2): ");
    scanf("%d", &counter);
    counter = counter - 1;
    while(!noMovesLeft(board)){
        counter++;
        if(counter%2 == 1){
            printf(" --> USER o: Select a row and coloumn to play your piece :");
            //cin>>row>>col;
            scanf("%d %d", &row, &col);
            row = row-1;
            col = col-1;
            printf("\n");
            if(board[row][col]=='_'){
                board[row][col] = 'o';
            }else{
                printf(" -->USER: Enter in empty locations <<endl");
                counter--;
            }
        }else{
            if (move == 0){
                row = 1; col = 1;
                board[row][col] = 'x';
                printf(" -->COMPUTER x: Selected row : %d and coloumn : %d\n", row, col);

            } else {
            struct move moveReturn;
            moveReturn = findBestMove(board,row,col);
            board[moveReturn.row][moveReturn.column] = 'x';
            printf(" -->COMPUTER x: Selected row : %d and coloumn : %d\n", row, col);
            }
        }
        move += 1;
        printBoard(board);
        if(evaluate(board) == 10){
            printf("\n         Better Luck next time\n\n         ---- Computer is the Winner ----\n");
            break;
        }else if(evaluate(board) == -10){
            printf("\n         Hurray\n         ---- U won ----\n");
            break;
        }
    }
    if(noMovesLeft(board)){
        printf("  Tied!! Try Again ....\n");
    }
}
// Main Function
int main(void){
    char board[3][3];
    // Game Play Controls the entire play
    gamePlay(board);
    printf("Total Call was: %d\n", total);
    return 0;
}
