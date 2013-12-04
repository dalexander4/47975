/* 
 * File:   main.cpp
 * Author: rcc
 *
 * Created on November 27, 2013, 2:37 PM
 */

#include <cstdlib>
#include <iostream>
#include <ctime>
#include "Players.h"
#include "Color.h"

using namespace std;

struct Board{
    char board[6][7];
    
};

void initBoard(Board&);
void displayRules();
void getNames();
void displayBoard(Board);
void chooseMove(Board&, int);
void PlayGame(Board&, int);
int HeadsTails();
bool TestScore(Board&,int, int);
/*
 * 
 */
int main(int argc, char** argv) {
    
    Board brd;
    int turn;
    color gtClr;
    
    initBoard(brd);
    displayRules();
    getNames();
    gtClr.setColor();
    turn = HeadsTails();
    PlayGame(brd, turn);
    
    
    
    
    return 0;
}
void initBoard(Board &set){
    
    for(int r = 0; r < 6; r++){
        for(int c = 0; c < 7; c++){
            set.board[r][c] = 'O';
        }
    }
}
void displayRules(){
    
    cout << "Welcome to connect four!" << endl;

}
void getNames(){
    string name1, name2;
    cout << "Enter the name of player 1: ";
    cin >> name1;
    cout << "Enter the name of player 2: ";
    cin >> name2;
    
    Players names;
    names.setPlayr(name1,name2);
}
int HeadsTails(){
    char coin, y;
    int x;
    
   
    do{
    cout << "\nWe will flip a coin to see who goes first!" << endl;
    cout << "Player 1 type H for heads or T for tails: ";
    cin >> coin;
    }while(coin != 'H' && coin != 'T');
    srand(time(0));
    //get random number for coin flip
    x=(rand()%2)+1;
    
    cout << "The coin flip was ";
    
    if (x==1){
        cout << "heads." << endl;
        y = 'H';
    }
    else if (x==2){
        cout << "tails." << endl;
        y = 'T';
    }
    
    if(coin == y){
        x = 1;
    }
    else x = 2;
    
    return x-1;
}
void PlayGame(Board &brd, int x){
    
    Players plyr;
    bool flag=false; //set flag to test for winner
    chooseMove(brd, x);
    x++;
    
    for(int i = 0; i < 41; i++){
        if(x>1)x=0;//return to the previous player.
        chooseMove(brd, x);
        
        x++;
        
        
        
        displayBoard(brd);
        
        //flag=TestScore(brd);
        if (flag==true) i = 45;//test to break out of loop.
    }
    cout << "There is no winner!" << endl;
    
}
void displayBoard(Board brd){
    cout << "C:  ";
    for(int i = 0; i < 7; i++){
        cout << i+1 <<"   ";
    }
    cout << endl;
    
     for(int r = 0; r < 6; r++){
        for(int c = 0; c < 7; c++){
            if(c==0)cout << r+1;
            
            cout << " | ";
            cout << brd.board[r][c];
        }
        cout<< " |";
        cout << endl;
    }
    cout << "  -----------------------------" << endl;
    
}
void chooseMove(Board &choice, int x){
    
    color clr;//declare a color object 
    int col, r = 6, count=0;
    bool doOvr;
    
    cout << clr.getPlayer(x) << " its your turn!" << endl;
  
    do{
        doOvr=true;
    cout << "What column would you like to drop your piece? (enter a column)" << endl;
    cout << "Column: ";
    cin >> col;
   
    cout << clr.getColor(x) << endl;
    
    for(int i = 5; i >= 0; i--){
        if(choice.board[i][col-1]== 'O'){//test to see if the column is taken
            choice.board[i][col-1] = clr.getColor(x);
            TestScore(choice, i, col-1);
            i = -1; 
        }
        else if(i == 0){//Test to see if the column is full
            cout << "Column full! Enter a different column!";
            doOvr=false;
        }
    }
    r--;//decrement the row.
    }while(doOvr == false);
    

}
bool TestScore(Board &brd, int r, int c){
    bool flag = false;
    int count = 0;
    
    if(c == 0){
        for(int i = 1; i<7; i++){
           if(brd.board[r][c]==brd.board[r][i]){
            count++;
            } 
        }
        
   
    }
    if(c == 1){
   
    }
    if(c == 2){
   
    }
    if(c == 3){
   
    }
    if(c == 4){
   
    }
    if(c == 5){
   
    }
    if(c == 6){
   
    }
  
    
    return flag;
}
