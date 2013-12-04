#include "Winner.h"
#include <iostream>

using namespace std;


void Winner::setWinner(int x){
    winner = x;
}
void Winner::getWinner(){
    cout << getPlayer(winner);
}