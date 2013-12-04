#include <cstdlib>
#include <iostream>
#include <string>
#include "Color.h"

using namespace std;
color::color(){
    clr[0] = 'Y';
    clr[1] = 'B';
}

void color::setColor(){
    
    int choice;
    /*
    for(int i = 0; i<2; i++){
        
    cout << getPlayer(i) << " choose a color: " << endl;
    cout << "1. Blue" << endl;
    cout << "2. Green" << endl;
    cout << "3. Yellow" << endl;
    cout << "4. Orange" << endl;
    cout << "5. White" << endl;
    cin >> choice;
    
    switch (choice){
        case 1: clr[i] = 'B';
        break;
        case 2: clr[i] = 'G';
        break;
        case 3: clr[i] = 'Y';
        break;
        case 4: clr[i] = 'O';
        break;
        case 5: clr[i] = 'W';
        break;
        default: break;
            
    }
    cout << endl;
    }
    */
}
char color::getColor(int x){
 
    return clr[x];
}