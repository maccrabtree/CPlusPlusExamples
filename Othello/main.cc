/*
Mac Crabtree

Main file for game program

*/

#include <iostream>
#include "space.h"
#include "game.h"
#include "othello.h"
#include <cstdlib>
#include <stack>
#include <queue>
using namespace std;

int main() {
    othello Game;
    main_savitch_14::game::who score = Game.play();
    if(score == main_savitch_14::game::HUMAN) cout << "Black ";
    else if(score == main_savitch_14::game::COMPUTER) cout << "White ";
    else if(score == main_savitch_14::game::NEUTRAL) cout << "Nobody ";
    cout << "wins the game!\n";
    cout << endl;
    return 0;
}

