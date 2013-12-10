/*
 * File:   Color.h
 * Author: rcc
 *
 * Created on December 2, 2013, 4:33 PM
 */

#ifndef COLOR_H
#define	COLOR_H
#include "Players.h"

class color: public Players{
    private:
        char clr[2];
    public:
        color();
        void setColor();
        char getColor(int);


};

#endif	/* COLOR_H */