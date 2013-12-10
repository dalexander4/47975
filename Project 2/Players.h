/*
 * File:   Players.h
 * Author: rcc
 *
 * Created on November 27, 2013, 3:50 PM
 */

#ifndef PLAYERS_H
#define	PLAYERS_H
#include <string>

class Players{
private:
    std::string plyr[2];
public:
    Players();
   void setPlayr(std::string,std::string);
   std::string getPlayer(int);
};


#endif	/* PLAYERS_H */
