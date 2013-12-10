#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include "GameBoard.h"
#include "Color.h"
using namespace std;
void GameBoard::initBoard(){
    
    Board='O';
    
}
char GameBoard::compareBoard(){
  
    return Board;
}
void GameBoard::setBoard(char x){
    
    Board = x;
}


