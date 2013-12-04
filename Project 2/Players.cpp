#include <cstdlib>
#include <iostream>
#include <string>
#include "Players.h"


using namespace std;

Players::Players(){
    plyr[0] = "Player 1";
    plyr[1] = "Player 2";
}

void Players::setPlayr(string x, string y){
    plyr[0] = x;
    plyr[1] = y;
    
}
string Players::getPlayer(int x){
       
return plyr[x];
}
