/*
 * File:   Final Project
 * Author: Dillin Alexander
 * Date: December 9th, 2013
 */

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <fstream>
#include "GameBoard.h"
#include "Players.h"
#include "Color.h"
#include "Winner.h"

using namespace std;



void displayRules(fstream&,fstream&);
void initBoard(GameBoard[][7]);
void getNames(Players&, fstream&);
bool chooseMove(GameBoard[][7], int,color&,fstream&);
void PlayGame(GameBoard[][7], int, Winner&,color&,fstream&);
int HeadsTails(fstream&);
bool TestScore(GameBoard[][7],int, int,fstream&);

int main(int argc, char** argv) {
    const int ROW=6,COL=7;
    //Declare two dimensional array of objects
    GameBoard bd[ROW][COL];
    //Declare object with 2 players.
    Players names;
    //Declare a p winner object
    Winner plyr;
    //declare a color object
    color clr;
    //Define integer to hold players turn
    int turn;
    //declare a file stream object
    fstream infile("file.txt",ios::in);
    //declare a file stream object
    fstream outfile("Game.txt", ios::out);
    //display the rules of the game
    displayRules(infile,outfile);
    //Initialize the game board
    initBoard(bd);
    //Get the names of the players
    getNames(names,outfile);
    //Have the players choose a color
    clr.setColor();
    //randomize who goes first
    turn = HeadsTails(outfile);
    //play game
    PlayGame(bd, turn, plyr, clr, outfile);


    infile.close();
    outfile.close();
    return 0;
}
void initBoard(GameBoard bd[][7]){
    //Initialize board pieces
    for(int i=0; i < 6; i++){
        for(int j=0; j<7; j++){
            bd[i][j].initBoard();
        }
    }
}
void displayRules(fstream &infile, fstream &ouput){
    string stuff;
    while(getline(infile,stuff)){

       cout << stuff << endl;
       ouput << stuff << endl;

    }
    cout << endl;

}
void getNames(Players &names, fstream &output){
    string name1,name2;

    //Get the players names
    cout << "Enter the name of player 1: ";
    output <<  "Enter the name of player 1: ";
    getline(cin,name1);
    output << name1 << endl;
    cout << "Enter the name of player 2: ";
    output <<  "Enter the name of player 2: ";
    getline(cin,name2);
    output << name2 << endl;
    names.setPlayr(name1,name2);
    
    cout << endl;
}
void displayBoard(GameBoard Board[][7], fstream &output){
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
            cout << Board[r][c].compareBoard();
            output << Board[r][c].compareBoard();
        }
        cout<< " |";
        output<< " |";
        cout << endl;
        output<<endl;
    }
    cout << "  -----------------------------" << endl;
    output <<"  -----------------------------" << endl;

}
int HeadsTails(fstream &output){
    //declare two character values
    char coin, y;
    int x;

    //loop until player 1 enters correct choice
    do{
    cout << "\nWe will flip a coin to see who goes first!" << endl;
    output << "\nWe will flip a coin to see who goes first!" << endl;
    cout << "Player 1 type H for heads or T for tails: ";
    output << "Player 1 type H for heads or T for tails: ";
    cin >> coin;
    output << coin << endl;
    }while(coin != 'H' && coin != 'T');
    srand(time(0));
    //get random number for coin flip
    x=(rand()%2)+1;
    //Output what the coin flip was!
    cout << "\nThe coin flip was ";
    output << "\nThe coin flip was ";

    if (x==1){
        cout << "heads." << endl;
        output << "heads." << endl;
        y = 'H';
    }
    else if (x==2){
        cout << "tails." << endl;
        output << "tails." << endl;
        y = 'T';
    }
    //set index equal to one
    if(coin == y){
        x = 1;
    }//or set index equal to two
    else x = 2;
    //return the index of the player who won the coin toss.
    return x-1;
}
void PlayGame(GameBoard brd[][7], int x, Winner &plyr, color &clr, fstream &output){

    bool flag=false; //set flag to test for winner
    //Whoever wins coin toss goes first
    chooseMove(brd, x,clr,output);
    //output first move
    displayBoard(brd, output);
    //increment to next player
    x++;
    //loop till we gone through all pieces on the board.
    for(int i = 0; i < 41; i++){
        //return to the previous player.
        if(x>1)x=0;
        //return true if a player wins, else return false.
        flag = chooseMove(brd, x, clr,output);
        //Display four square board
        displayBoard(brd,output);
        //If a winner is decided break
        if(flag==true){
            plyr.AnnceWinner(x);
            break;
        }
        //Increment player count
        x++;

        //test to break out of loop if winner declared
        if (flag==true) i = 45;
    }
    //If no winner declared then there is a tie.
    if(flag==false){
    cout << "There is Draw!" << endl;
    output << "There is a Draw!" << endl;
    }

}
bool chooseMove(GameBoard Board[][7], int x, color &clr, fstream &output){


    int col=0, r = 6;
    bool doOvr, win = false;

    cout << clr.getPlayer(x) << " its your turn!" << endl;
    output << clr.getPlayer(x) << " its your turn!" << endl;

    do{
        doOvr=true;
        //Test to validate that the input is between one and seven.
        do{
        cout << "What column would you like to drop your piece? (enter a column number)" << endl;
        output << "What column would you like to drop your piece? (enter a column number)" << endl;
        cout << "Column: ";
        output << "Column: ";
        cin >> col;
        output << col << endl;
        }while(col!=1&&col!=2&&col!=3&&col!=4&&col!=5&&col!=6&&col!=7);
    cout << clr.getColor(x) << endl;
    output << clr.getColor(x) << endl;
    
    for(int i = 5; i >= 0; i--){
        //test to see if the column is taken
        if(Board[i][col-1].compareBoard()== 'O'){
            char y = clr.getColor(x);
            Board[i][col-1].setBoard(y);
            //test to see if the players choice makes four in a row
            win = TestScore(Board, i, col-1,output);
            i = -1;
        }
        else if(i == 0){//Test to see if the column is full
            cout << "Column full! Enter a different column!";
            output << "Column full! Enter a different column!";
            doOvr=false;
        }
    }
    r--;//decrement the row.
    }while(doOvr == false);

    return win;
}
bool TestScore(GameBoard Board[][7], int r, int c, fstream &output){
    bool flag = false;
    int count = 1;
    int Dcount = 1,Dcount2 =1,Dcount3 =1,Dcount4 =1,Vcount = 1;
    int Pcount=0,Ncount=0;
    int t=r;

    //Test to see if the choice is in the first column.
    if(c == 0){
        for(int i = c+1; i<7; i++){
           if(Board[r][c].compareBoard()==Board[r][i].compareBoard()){
            count++;
            }
           else break;
        }
    }
     //Test to see if the choice is in the second column.
    if(c == 1){
        for(int i = c+1; i<7; i++){
           if(Board[r][c].compareBoard()==Board[r][i].compareBoard()){
            count++;
            }
           else break;
        }
        for(int j = c-1; j>=0; j--){
           if(Board[r][c].compareBoard()==Board[r][j].compareBoard()){
            count++;
            }
           else break;
        }
    }
     //Test to see if the choice is in the third column.
    if(c == 2){
        for(int i = c+1; i<7; i++){
           if(Board[r][c].compareBoard()==Board[r][i].compareBoard()){
            count++;
            }
           else break;
        }
        for(int j = c-1; j>=0; j--){
           if(Board[r][c].compareBoard()==Board[r][j].compareBoard()){
            count++;
            }
           else break;
        }
    }
     //Test to see if the choice is in the fourth column.
    if(c == 3){
        for(int i = c+1; i<7; i++){
           if(Board[r][c].compareBoard()==Board[r][i].compareBoard()){
            count++;
            }
           else break;
        }
        for(int j = c-1; j>=0; j--){
           if(Board[r][c].compareBoard()==Board[r][j].compareBoard()){
            count++;
            }
           else break;
        }
    }
     //Test to see if the choice is in the five column.
    if(c == 4){
        for(int i = c+1; i<7; i++){
           if(Board[r][c].compareBoard()==Board[r][i].compareBoard()){
            count++;
            }
           else break;
        }
        for(int j = c-1; j>=0; j--){
           if(Board[r][c].compareBoard()==Board[r][j].compareBoard()){
            count++;
            }
           else break;
        }
    }
     //Test to see if the choice is in the sixth column.
    if(c == 5){
        for(int i = c+1; i<7; i++){
           if(Board[r][c].compareBoard()==Board[r][i].compareBoard()){
            count++;
            }
           else break;
        }
        for(int j = c-1; j>=0; j--){
           if(Board[r][c].compareBoard()==Board[r][j].compareBoard()){
            count++;
            }
           else break;
        }
    }
     //Test to see if the choice is in the seventh column.
    if(c == 6){
        for(int i = c+1; i<7; i++){
           if(Board[r][c].compareBoard()==Board[r][i].compareBoard()){
            count++;
            }
           else break;
        }
        for(int j = c-1; j>=0; j--){
           if(Board[r][c].compareBoard()==Board[r][j].compareBoard()){
            count++;
            }
           else break;
        }
    }
    //Start testing for horizontal connections
    if(c>=0&&c<=6){
        for(int i = r+1; i<6; i++){
           if(Board[r][c].compareBoard()==Board[i][c].compareBoard()){
            Vcount++;
            }
           else break;
        }
        for(int j = r-1; j>=0; j--){
           if(Board[r][c].compareBoard()==Board[j][c].compareBoard()){
            Vcount++;
            }
           else break;
        }
    }
    //Start testing for diagonal connections
    //Begin with the first column
    if(c == 0 && r==5){
            for(int i = c+1; i<6; i++){//Diagonal count up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount++;
                }
                else break;
            }
        }
    if(c == 0 && r==4){
            for(int i = c+1; i<5; i++){//Diagonal count up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount++;
                }
            else break;
            }
            for(int i = c+1; i<2; i++){//Diagonal count down
                t=r;
                t++;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount2++;
                }
                else break;
            }

        }
    if(c == 0 && r==3){
            for(int i = c+1; i<4; i++){//count up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount++;
                }
            else break;
            }t=r;
            for(int i = c+1; i<3; i++){//count down
                t++;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount2++;
                }
                else break;
            }
        }
    if(c == 0 && r==2){
            for(int i = c+1; i<3; i++){//count up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount++;
                }
                else break;
            }t=r;
            for(int i = c+1; i<4; i++){

                t++;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount2++;
                }
                else break;
            }
        }
    if(c == 0 && r==1){
            for(int i = c+1; i<2; i++){
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount++;
                }
                else break;
            }t=r;
            for(int i = c+1; i<5; i++){

                t++;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount2++;
                }
                else break;
            }
        }
    if(c == 0 && r==0){
            for(int i = c+1; i<6; i++){
                t++;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount2++;
                }
                else break;
            }
        }
    //Continue diagonal search
    //Begin count for second column
    if(c == 1 && r==5){
            for(int i = c+1; i<6; i++){
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount++;
                }
                else break;
            }
            for(int i = c-1; i>=0; i--){//count back up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount3++;
                }
                else break;
            }

        }
    if(c == 1 && r==4){
            for(int i = c+1; i<5; i++){//count up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount++;
                }
            else break;
            }t=r;
            for(int i = c+1; i<3; i++){//count down
                t++;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount2++;
                }
                else break;
            }t=r;
            for(int i = c-1; i>=0; i--){//count back up

                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount3++;
                }
                else break;
            }t=r;
            for(int i = c-1; i>=0; i--){//count back down

                t++;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount4++;
                }
                else break;
            }

        }
    if(c == 1 && r==3){
            for(int i = c+1; i<4; i++){//count up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount++;
                }
            else break;
            }t=r;
            for(int i = c+1; i<4; i++){//count down
                t++;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount2++;
                }
                else break;
            }t=r;
            for(int i = c-1; i>=0; i--){//count back up

                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount3++;
                }
                else break;
            }t=r;
            for(int i = c-1; i>=0; i--){//count back down

                t++;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount4++;
                }
                else break;
            }
        }
    if(c == 1 && r==2){
            for(int i = c+1; i<3; i++){//count up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount++;
                }
                else break;
            }t=r;
            for(int i = c+1; i<5; i++){//count down
                t++;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount2++;
                }
                else break;
            }t=r;
            for(int i = c-1; i>=0; i--){//count back up

                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount3++;
                }
                else break;
            }t=r;
            for(int i = c-1; i>=0; i--){//count back down

                t++;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount4++;
                }
                else break;
            }
        }
    if(c == 1 && r==1){
            for(int i = c+1; i<2; i++){//count up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount++;
                }
                else break;
            }t=r;
            for(int i = c+1; i<5; i++){//count down

                t++;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount2++;
                }
                else break;
            }t=r;
            for(int i = c-1; i>=0; i--){//count back up

                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount3++;
                }
                else break;
            }t=r;
            for(int i = c-1; i>=0; i--){//count back down

                t++;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount4++;
                }
                else break;
            }
        }
    if(c == 1 && r==0){
            for(int i = c+1; i<6; i++){//count down
                t++;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount2++;
                }
                else break;
            }
        }
    //Continue diagonal search
    //Begin count for third column
    if(c == 2 && r==5){
            for(int i = c+1; i<6; i++){
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount++;
                }
                else break;
            }
            for(int i = c-1; i>=0; i--){//count back up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount3++;
                }
                else break;
            }

        }
    if(c == 2 && r==4){
            for(int i = c+1; i<5; i++){//count up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount++;
                }
            else break;
            }t=r;
            for(int i = c+1; i<4; i++){//count down
                t++;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount2++;
                }
                else break;
            }t=r;
            for(int i = c-1; i>=0; i--){//count back up

                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount3++;
                }
                else break;
            }t=r;
            for(int i = c-1; i>=0; i--){//count back down

                t++;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount4++;
                }
                else break;
            }

        }
    if(c == 2 && r==3){
            for(int i = c+1; i<4; i++){//count up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount++;
                }
            else break;
            }t=r;
            for(int i = c+1; i<5; i++){//count down

                t++;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount2++;
                }
                else break;
            }t=r;
            for(int i = c-1; i>=0; i--){//count back up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount3++;
                }
                else break;
            }t=r;
            for(int i = c-1; i>=0; i--){//count back down

                t++;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount4++;
                }
                else break;
            }
        }
    if(c == 2 && r==2){
            for(int i = c+1; i<3; i++){//count up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount++;
                }
                else break;
            }t=r;
            for(int i = c+1; i<6; i++){//count down
                t++;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount2++;
                }
                else break;
            }t=r;
            for(int i = c-1; i>=0; i--){//count back up

                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount3++;
                }
                else break;
            }t=r;
            for(int i = c-1; i>=0; i--){//count back down

                t++;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount4++;
                }
                else break;
            }
        }
    if(c == 2 && r==1){
            for(int i = c+1; i<2; i++){//count up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount++;
                }
                else break;
            }t=r;
            for(int i = c+1; i<7; i++){//count down
                t++;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount2++;
                }
                else break;
            }t=r;
            for(int i = c-1; i>=0; i--){//count back up

                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount3++;
                }
                else break;
            }t=r;
            for(int i = c-1; i>=0; i--){//count back down

                t++;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount4++;
                }
                else break;
            }
        }
    if(c == 2 && r==0){
            for(int i = c+1; i<6; i++){//count down
                t++;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount2++;
                }
                else break;
            }t=r;
            for(int i = c-1; i>=0; i--){//count back down
                t++;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount4++;
                }
                else break;
            }
        }
    //Continue diagonal search
    //Begin count for fourth column
    if(c == 3 && r==5){
            for(int i = c+1; i<6; i++){//count up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount++;
                }
                else break;
            }t=r;
            for(int i = c-1; i>=0; i--){//count back up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount3++;
                }
                else break;
            }
        }
    if(c == 3 && r==4){
            for(int i = c+1; i<5; i++){//count up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount++;
                }
            else break;
            }t=r;
            for(int i = c+1; i<5; i++){//count down
                t++;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount2++;
                }
                else break;
            }t=r;
            for(int i = c-1; i>=0; i--){//count back up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount3++;
                }
                else break;
            } t=r;
            for(int i = c-1; i>=0; i--){//count back down

                t++;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount4++;
                }
                else break;
            }

        }
    if(c == 3 && r==3){
            for(int i = c+1; i<4; i++){//count up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount++;
                }
            else break;
            }t=r;
            for(int i = c+1; i<6; i++){//count down
                t++;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount2++;
                }
                else break;
            }t=r;
            for(int i = c-1; i>=0; i--){//count back up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount3++;
                }
                else break;
            }t=r;
            for(int i = c-1; i>=0; i--){//count back down
                t++;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount4++;
                }
                else break;
            }
        }
    if(c == 3 && r==2){
            for(int i = c+1; i<3; i++){//count up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount++;
                }
                else break;
            }t=r;
            for(int i = c+1; i<7; i++){//count down
                t++;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount2++;
                }
                else break;
            }t=r;
            for(int i = c-1; i>=0; i--){//count back up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount3++;
                }
                else break;
            }t=r;
            for(int i = c-1; i>=0; i--){//count back down
                t++;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount4++;
                }
                else break;
            }
        }
    if(c == 3 && r==1){
            for(int i = c+1; i<2; i++){//count up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount++;
                }
                else break;
            }t=r;
            for(int i = c+1; i<7; i++){//cound down
                t++;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount2++;
                }
                else break;
            }t=r;
            for(int i = c-1; i>=0; i--){//count back up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount3++;
                }
                else break;
            }t=r;
            for(int i = c-1; i>=0; i--){//count back down
                t++;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount4++;
                }
                else break;
            }
        }
    if(c == 3 && r==0){
            for(int i = c+1; i<7; i++){//count down
                t++;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount2++;
                }
                else break;
            }t=r;
            for(int i = c-1; i>=0; i--){//count back down
                t++;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount4++;
                }
                else break;
            }
        }
    //Continue diagonal search
    //Begin count for fifth column
    if(c == 4 && r==5){
            for(int i = c+1; i<6; i++){//count up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount++;
                }
                else break;
            }
            t=r;
            for(int i = c-1; i>=0; i--){//count back up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount3++;
                }
        }
    }
    if(c == 4 && r==4){
            for(int i = c+1; i<5; i++){//count up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount++;
                }
            else break;
            }t=r;
            for(int i = c+1; i<6; i++){//count down
                t++;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount2++;
                }
                else break;
            }t=r;
            for(int i = c-1; i>=0; i--){//count back up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount3++;
                }
                else break;
            }t=c;
            for(int i = r+1; i<6; i++){//count back down
                t--;
                if(Board[r][c].compareBoard()==Board[i][t].compareBoard()){
                Dcount4++;
                }
                else break;
            }

        }
    if(c == 4 && r==3){
            for(int i = c+1; i<4; i++){//count up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount++;
                }
            else break;
            }t=r;
            for(int i = c+1; i<7; i++){//count down
                t++;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount2++;
                }
                else break;
            }t=r;
            for(int i = c-1; i>=0; i--){//count back up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount3++;
                }
                else break;
            }t=c;
            for(int i = r+1; i<6; i++){//count back down
                t--;
                if(Board[r][c].compareBoard()==Board[i][t].compareBoard()){
                Dcount4++;
                }
                else break;
            }
        }
    if(c == 4 && r==2){
            for(int i = c+1; i<3; i++){//count up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount++;
                }
                else break;
            }t=r;
            for(int i = c+1; i<7; i++){//count down
                t++;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount2++;
                }
                else break;
            }t=r;
            for(int i = c-1; i>=0; i--){//count back up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount3++;
                }
                else break;
            }t=c;
            for(int i = r+1; i<6; i++){//count back down
                t--;
                if(Board[r][c].compareBoard()==Board[i][t].compareBoard()){
                Dcount4++;
                }
                else break;
            }
        }
    if(c == 4 && r==1){
            for(int i = c+1; i<2; i++){//count up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount++;
                }
                else break;
            } t=r;
            for(int i = c+1; i<7; i++){//count down
                t++;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount2++;
                }
                else break;
            }t=r;
            for(int i = c-1; i>=0; i--){//count back up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount3++;
                }
                else break;
            }t=c;
            for(int i = r+1; i<6; i++){//count back down
                t--;
                if(Board[r][c].compareBoard()==Board[i][t].compareBoard()){
                Dcount4++;
                }
                else break;
            }
        }
    if(c == 4 && r==0){
            for(int i = c+1; i<7; i++){
                t++;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount2++;
                }
                else break;
            }
        }
    //Continue diagonal search
    //Begin count for sixth column
    if(c == 5 && r==5){
            for(int i = c+1; i<7; i++){//count up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount++;
                }
                else break;
            }t=r;
            for(int i = c-1; i>=0; i--){//count back up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount3++;
                }
                else break;
        }
    }
    if(c == 5 && r==4){
            for(int i = c+1; i<5; i++){//count up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount++;
                }
            else break;
            }t=r;
            for(int i = c+1; i<7; i++){//count down
                t++;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount2++;
                }
                else break;
            }t=r;
            for(int i = c-1; i>=0; i--){//count back up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount3++;
                }
                else break;
            }t=c;
            for(int i = r+1; i<6; i++){//count back down
                t--;
                if(Board[r][c].compareBoard()==Board[i][t].compareBoard()){
                Dcount4++;
                }
                else break;
            }

        }
    if(c == 5 && r==3){
            for(int i = c+1; i<4; i++){//count up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount++;
                }
            else break;
            }t=r;
            for(int i = c+1; i<7; i++){//count down
                t++;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount2++;
                }
                else break;
            }t=r;
            for(int i = c-1; i>=0; i--){//count back up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount3++;
                }
                else break;
            }t=c;
            for(int i = r+1; i<6; i++){//count back down
                t--;
                if(Board[r][c].compareBoard()==Board[i][t].compareBoard()){
                Dcount4++;
                }
                else break;
            }
        }
    if(c == 5 && r==2){
            for(int i = c+1; i<3; i++){//count up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount++;
                }
                else break;
            }t=r;
            for(int i = c+1; i<7; i++){//count down
                t++;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount2++;
                }
                else break;
            }t=r;
            for(int i = c-1; i>=0; i--){//count back up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount3++;
                }
                else break;
            }t=c;
            for(int i = r+1; i<6; i++){//count back down
                t--;
                if(Board[r][c].compareBoard()==Board[i][t].compareBoard()){
                Dcount4++;
                }
                else break;
            }
        }
    if(c == 5 && r==1){
            for(int i = c+1; i<2; i++){//count up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount++;
                }
                else break;
            }t=r;
            for(int i = c+1; i<7; i++){//count down
                t++;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount2++;
                }
                else break;
            }t=r;
            for(int i = c-1; i>=0; i--){//count back up
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount3++;
                }
                else break;
            }t=c;
            for(int i = r+1; i<6; i++){//count back down
                t--;
                if(Board[r][c].compareBoard()==Board[i][t].compareBoard()){
                Dcount4++;
                }
                else break;
            }
        }
    if(c == 5 && r==0){
            for(int i = c+1; i<7; i++){//count down
                t++;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount2++;
                }
                else break;
            }
            for(int i = r+1; i<6; i++){//count back down
                t--;
                if(Board[r][c].compareBoard()==Board[i][t].compareBoard()){
                Dcount4++;
                }
                else break;
            }
        }
    //Continue diagonal search
    //Begin count for Seventh column
    if(c == 6 && r==5){
            for(int i = c-1; i<0; i--){
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount3++;
                }
                else break;
            }
        }
    if(c == 6 && r==4){
            for(int i = c-1; i<0; i--){
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount3++;
                }
            else break;
            }t=c;
            for(int i = r+1; i<6; i++){
                t--;
                if(Board[r][c].compareBoard()==Board[i][t].compareBoard()){
                Dcount4++;
                }
                else break;
            }

        }
    if(c == 6 && r==3){
            for(int i = c-1; i<0; i--){
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount3++;
                }
            else break;
            }t=c;
            for(int i = r+1; i<6; i++){
                t--;
                if(Board[r][c].compareBoard()==Board[i][t].compareBoard()){
                Dcount4++;
                }
                else break;
            }
        }
    if(c == 6 && r==2){
            for(int i = c-1; i<0; i--){
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount3++;
                }
            else break;
            }t=c;
            for(int i = r+1; i<6; i++){
                t--;
                if(Board[r][c].compareBoard()==Board[i][t].compareBoard()){
                Dcount4++;
                }
                else break;
            }
        }
    if(c == 6 && r==1){
            for(int i = c-1; i<0; i--){
                t--;
                if(Board[r][c].compareBoard()==Board[t][i].compareBoard()){
                Dcount3++;
                }
            else break;
            }t=c;
            for(int i = r+1; i<6; i++){
                t--;
                if(Board[r][c].compareBoard()==Board[i][t].compareBoard()){
                Dcount4++;
                }
                else break;
            }
        }
    if(c == 6 && r==0){
            for(int i = r+1; i<6; i++){
                t--;
                if(Board[r][c].compareBoard()==Board[i][t].compareBoard()){
                Dcount4++;
                }
                else break;
            }
        }
    cout << "Diagonal up " << Dcount<< endl;
    cout << "Diagonal down " << Dcount2<< endl;
    cout << "Diagonal back up " << Dcount3<< endl;
    cout << "Diagonal back down " << Dcount4<< endl;
    


    //Adding up the slopes
    if(Dcount==1)Dcount=0;
    if(Dcount4==1)Dcount4=0;
    Pcount=Dcount+Dcount4;//Adding up the positive diagonal slope
    if(Pcount==0)Pcount=1;

    if(Dcount2==1)Dcount2=0;
    if(Dcount3==1)Dcount3=0;
    Ncount=Dcount2+Dcount3;//Adding up the negative diagonal slope
    if(Ncount==0)Ncount=1;

    //Output the amount the player got in a row.
    cout << "\n_____________________________________" << endl;
    output << "\n_____________________________________" << endl;
    cout << "horizontal count =                 " << count << " |" << endl;
    output << "horizontal count =                 " << count << " |" << endl;
    cout << "Vertical count =                   " << Vcount << " |" <<  endl;
    output << "Vertical count =                   " << Vcount << " |" <<  endl;
    cout << "Diagonal count (Positive slope) =  " << Pcount << " |" << endl;
    output << "Diagonal count (Positive slope) =  " << Pcount << " |" << endl;
    cout << "Diagonal count (Negative slope) =  " << Ncount << " |" << endl;
    output << "Diagonal count (Negative slope) =  " << Ncount << " |" << endl;
    cout << "-------------------------------------" << endl<<endl;
    output << "-------------------------------------" << endl<<endl;

    //if a player gets to four send a flag
    if(count >= 4)flag =true;
    if(Pcount >= 4)flag =true;
    if(Ncount >= 4)flag =true;
    if(Vcount >= 4)flag =true;

    return flag;
}

