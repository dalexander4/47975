
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include "GameBoard.h"

GameBoard::GameBoard(){
    for(int r = 0; r < 6; r++){
        for(int c = 0; c < 7; c++){
            board[r][c] = 'O';
        }
    }
}
}
void GameBoard::SetBoard(){
    
}
void GameBoard::DisplayBoard(){
    cout << "C:  ";
    output << "C:  ";
    for(int i = 0; i < 7; i++){
        cout << i+1 <<"   ";
        output << i+1 <<"   ";
    }
    cout << endl;
    output << endl;

     for(int r = 0; r < 6; r++){
        for(int c = 0; c < 7; c++){
            if(c==0){
                    cout << r+1;
                    output << r+1;
            }
            cout << " | ";
            output << " | ";
            cout << Board[r][c];
            output << Board[r][c];
        }
        cout<< " |";
        output<< " |";
        cout << endl;
        output<<endl;
    }
    cout << "  -----------------------------" << endl;
    output <<"  -----------------------------" << endl;

}
