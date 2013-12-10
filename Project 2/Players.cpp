#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include "Players.h"
#include "Color.h"
#include "Winner.h"


using namespace std;
Players::Players(){
    *(plyr+0) = "Player 1";
    *(plyr+1) = "Player 2";
}

void Players::setPlayr(string x, string y){

    fstream name1, name2;
    name1.open("Player 1.txt",ios::out);
    name2.open("Player 2.txt",ios::out) ;


   name1 << x;
   name2 << y;

}
std::string Players::getPlayer(int x){

string file;

    fstream name1, name2;
    name1.open("Player 1.txt",ios::in);
    name2.open("Player 2.txt",ios::in) ;

if(x==0)name1>>file;
if(x==1)name2>>file;

name1.close();
name2.close();

return file;
}
