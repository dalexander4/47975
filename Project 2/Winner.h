/*
 * File:   Winner.h
 * Author: rcc
 *
 * Created on December 4, 2013, 11:44 AM
 */

#ifndef WINNER_H
#define	WINNER_H
#include "Players.h"
#include <string>

class Winner: public Players{
    private:
        int winner;
    public:
        void AnnceWinner(int);

};

#endif	/* WINNER_H */
