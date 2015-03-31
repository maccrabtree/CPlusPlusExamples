/*
Mac Crabtree
Game project

Othello class, child of game class
used with othello.cc and requires space.h and game.h
Contains majority of workings of game Othello

07/23/12
*/


#include "game.h"
#include "space.h"
#include <queue>
#include <string>
#ifndef OTHELLO
#define OTHELLO

class othello:public main_savitch_14::game {
    public:
         othello(); //default constructor, puts starting four pieces
                    //in their appropriate places

         void display_status() const; //shows the board

         void make_move(const std::string& move);
         //takes in the move string, and flips the appropriate pieces          
                
         bool is_legal(const std::string& move) const;
         //Determines whether or not a user inputted move is legal
         //to make or not

         game* clone() const; //currently stubbed

         void compute_moves(std::queue<std::basic_string<char> >& q) const;
         //takes a queue as an argument, and will go through every 
         //possible game piece, and decide whether a move can be made 
         //there or not with the is_legal function. If a move can be made
         //it is pushed onto the queue
         
         int evaluate() const; //This sums together all pieces on board
         //If there are more whites than blacks, returns negative
         //If there are more blacks than whites, returns positive
         //If it is a tie, it will return 0


         bool is_game_over() const; //will return true if there are 
         //no more pieces of either side, no more blanks, or if there
         //are no moves left by either people, as indicated by two passes
         
         bool can_pass() const;
         //will call the compute_moves function, and return true only
         //if the queue returns empty from compute_moves, meaning no  
         //move available
    private:
    space Board[8][8]; //64 piece square, used as game board
    bool pass; //Used for end-game pass analysis, true when pass is made
    bool game_over;    
    //Helper functions for checking move possibilities
    bool west(std::string& move) const;
    bool east(std::string& move) const;
    bool north(std::string& move) const;
    bool south(std::string& move) const;
    bool northwest(std::string& move) const;
    bool northeast(std::string& move) const;
    bool southwest(std::string& move) const;
    bool southeast(std::string& move) const;

};

#endif
