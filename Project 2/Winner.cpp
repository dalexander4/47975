#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include "Players.h"
#include "Color.h"
#include "Winner.h"

using namespace std;


void Winner::AnnceWinner(int x){
    winner = x;
    ofstream output;
    output.open("Game.txt",ios::app);
    cout << "The winner is " << getPlayer(x) << endl;
    output << "\nThe winner is " << getPlayer(x) << endl;
    cout << "Congratulations!!!!" << endl;
    output << "Congratulations!!!!" << endl;
}

