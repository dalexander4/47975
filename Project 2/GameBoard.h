/* 
 * File:   GameBoard.h
 * Author: rcc
 *
 * Created on December 9, 2013, 9:07 AM
 */

#ifndef GAMEBOARD_H
#define	GAMEBOARD_H
#include "Color.h"

class GameBoard: public color{
private: 
    char Board;
public:
    void initBoard();
    char compareBoard();
    void setBoard(char);
    void displayBoard();
    
};


#endif	/* GAMEBOARD_H */

