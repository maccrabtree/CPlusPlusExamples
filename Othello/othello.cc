/*
Mac Crabtree
Othello class definitions
For use with othello.cc

contains all class definitions for othello class declarations

07/23/2012
*/


#include "othello.h"
#include "game.h"
#include "colors.h"
#include "space.h"
#include <iostream>
#include <cstdlib>
using namespace std;

othello::othello() {
    Board[3][3].to_black(); //Northwest Black
    Board[4][4].to_black(); //Southeast Black
    Board[3][4].to_white(); //Northeast White
    Board[4][3].to_white(); //Southwest White
    pass = false;
    game_over = false;
}

void othello::display_status() const{
    cout << WHITE << "   1  2  3  4  5  6  7  8\n"; //Top COlumn Headings

    char row = 'A'; //Will increment and be row headings for each row

    for(int i = 0; i < 8; i++) {
       cout << row << " "; //Row is the letter number of the row

       for(int j = 0; j < 8; j++) {
           cout << B_MAGENTA; 
           //gives the board a background of magenta
           //I chose magenta because it made both white and black
           //stand out while not being too hard on the eyes

           switch(Board[i][j].get_color()) { 
           //Will flip to appropriate board coloring, depending on
           //what that particular space is currently set to 

              case 0:       //Empty Space
                  cout << GREEN << " - ";
                  break;
              case 1:       //White Piece
                  cout << WHITE << " O "; 
                  break;  
              case 2:       //Black Piece
                  cout << BLACK << " O ";
                  break;
           }
           cout << RESET; //Puts the background to normal after every loop
         }
           cout << WHITE << " " << row << " \n"; //Row Letter for other side
           //of board
           row++; //Increments row letter, A to B, B to C, etc.
       }
    cout << "   1  2  3  4  5  6  7  8\n"; //Col numbers for bott. of board
    cout << RESET;  //puts color back to normal
}

main_savitch_14::game* othello::clone() const {
  /*
  game* tmp;
  tmp = new othello;
  for(int i = 0; i < 8; i++) {
     for(int j = 0; j < 8; j++) {
        tmp->Board[i][j].set_color(Board[i][j].get_color());
     }
  }
  return tmp;
    */
  othello copy_game;
  copy_game = *this;
  othello* tmp = new othello;
  *tmp = copy_game;
  return tmp;       
}

void othello::make_move(const std::string& move) {
  int row, col, the_color;
  if(move == "pass") {
     if(pass == true) game_over = true; //meaning, if the last
                          //move was also a pass, the game is over
     else pass = true;
     game::make_move(move); //increment turn number still
     return;
  }
  string the_move = move; //changes to non-const string for helper function
  row = toupper(int(move[0])); //changes first letter to uppercase
  //so user may enter lowercase letters and still function correctly

  row = int(row - 'A');
  col = int(move[1] - '1');
  int restart_row = row; //restart_row and restart_col serve as the
  int restart_col = col; //original starting point, so after each call
                         //to flipping a direction, it comes back
                         //to be able to flip from another direction
  if(next_mover() == HUMAN) {
      Board[row][col].to_black(); //flip the piece to black
      the_color = 2; //enemy color is white
  }
  else {
      Board[row][col].to_white();  //flip the piece to white
      the_color = 1;               //enemy color is black
  }


  //The rest of this function checks which directions have valid
  //moves, and then flips the pieces accordingly in those directions
  //until it reaches another piece of its color


  if(east(the_move)) {
      col++;
      while(Board[row][col].get_color() != the_color) {
          Board[row][col].flip();
          col++;
      } 
  }
  col = restart_col;
  if(west(the_move)) {
      col--;
      while(Board[row][col].get_color() != the_color) {
          Board[row][col].flip();
          col--;
      }
  }
  col = restart_col;
  if(south(the_move)) {
      row++;
      while(Board[row][col].get_color() != the_color) {
          Board[row][col].flip();
          row++;
      }
  }
  row = restart_row;
  if(north(the_move)) {
      row--;
      while(Board[row][col].get_color() != the_color) {
          Board[row][col].flip();
          row--;
      }
  }
  row = restart_row;      
  
  if(northwest(the_move)) {
      row--;
      col--;
      while(Board[row][col].get_color() != the_color) {
          Board[row][col].flip();
          row--;
          col--;
      }
  }
  row = restart_row;
  col = restart_col;

  if(southwest(the_move)) {
     row++;
     col--;
     while(Board[row][col].get_color() != the_color) {
          Board[row][col].flip();
          row++;
          col--;
     }
  row = restart_row;
  col = restart_col;
  }
  if(northeast(the_move)) {
     row--;
     col++;
     while(Board[row][col].get_color() != the_color) {
          Board[row][col].flip();
          row--;
          col++;
     }
   }
   row = restart_row;
   col = restart_col;
   
   if(southeast(the_move)) {
     row++;
     col++;
     while(Board[row][col].get_color() != the_color) {
          Board[row][col].flip();
          row++;
          col++;
     }
   }
 game::make_move(move); //increments the move turn
 pass = false; //shows that a move occured and game cannot end

}


bool othello::is_legal(const std::string& move) const {
  
  string the_move = move; //makes move non-const
  if(move == "pass") {
  return(can_pass());
  }
  int row, col;
  row = int(toupper(move[0]) - 'A');
  col = int(move[1] - '1');
  if(row < 0 || row > 7 || col < 0 || col > 7) return false;
  if(Board[row][col].get_color() != 0) return false; //check if the space is empty
  //The rest of this function will return true if any of the directions
  //Have a valid move, and false if not
  if(west(the_move)) return true;
  else if(east(the_move)) return true;
  else if(south(the_move)) return true;
  else if(north(the_move)) return true;
  else if(northwest(the_move)) return true;
  else if(northeast(the_move)) return true;
  else if(southwest(the_move)) return true;
  else if(southeast(the_move)) return true;
  else return false;
  
}

void othello::compute_moves(std::queue<std::basic_string<char> >& q) const {
    for(char row = 'A'; row < 'I'; row++) {
        for(char col = '1'; col < '8'; col++) {
            string the_move("tmp");
            the_move[0] = row;
            the_move[1] = col;
            if(is_legal(the_move)) { 
                 q.push(the_move); //Only push if move is valid
            }
        }
    }
    if(q.empty()) {
         string the_move("pass");
         q.push(the_move);
    }


}

bool othello::can_pass() const {
    std::queue<std::basic_string<char> > q;
    compute_moves(q);
    if(q.front() == "pass") return true; //meaning, no possible moves
    else return false; //meaning, there are still possible moves

   
}

int othello::evaluate() const { //Whites pieces add, blacks subtract
                                //Blanks do nothing
    int score = 0;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
           switch(Board[i][j].get_color()) {
               case 0:          //Blank, do nothing
                     break; 
               case 1: 
                     score++;  //White, add
                     break;
               case 2:
                     score--; //Black, subtract
                     break;
          }
        }
    }
    return score; //positive if white winning, negative black, 0 neutral
}

bool othello::is_game_over() const {
   if(game_over == true) return true; //Which is true when 2 
                                     //consecutive passes have occured
   int blacks = 0, whites = 0, empty = 0;
   for(int i = 0; i < 8; i++) {
      for(int j = 0; j < 8; j++) {
         if(Board[i][j].get_color() == 0) empty++;
         else if(Board[i][j].get_color() == 1) whites++;
         else if(Board[i][j].get_color() == 2) blacks++;
      } //Add up all of the pieces of every color
   }
   if(whites == 0 || blacks == 0 || empty == 0) return true;
   //If any of the colors have zero pieces, no moves can be made 
   //Game over
   else return false;
}


//All looking helper functions
//All these functions do are take the move given, 
//Seperate it into row and column,
//and then according to their direction, start tracing the 
//Opponents color from their original start
//If at least one opponents color is hit before ending the loop
//The bool flip becomes true.
//After the loop goes through tracing, the ending point determines
//Whether or not it is legal to move
//If the loops end on an empty space, then no move can be made
//If it ends out of the borders of the game, no move can be made
//Only if it ends on its own color again, with at least one flip being 
//possible, can a move be made
//Over a column is col++, over a row is row++, with back a col and row 
//Being the opposite. 

bool othello::west(string& move) const {
   int row = int(toupper(move[0]) - 'A');
   int col = int(move[1] - '1');
   int the_color, other_color;
   bool flip = false;
   if(game::next_mover() == HUMAN) {
	the_color = 1;
        other_color = 2;
   }
   else if(game::next_mover() == COMPUTER) {
        the_color = 2;
        other_color = 1;
   }
   col--;
   while(col >= 0 && Board[row][col].get_color() == the_color) {
       col--;
       flip = true;
    }
   if(col == -1) return false;
   else if(Board[row][col].get_color() == 0) return false;
   else return flip;
      
}

bool othello::east(string& move)const {
    int row = int(toupper(move[0]) - 'A');
    int col = int(move[1] - '1');
    int the_color, other_color;
    bool flip = false;
    if(game::next_mover() == HUMAN) {
        the_color = 1;
        other_color = 2;
    }
    else if(game::next_mover() == COMPUTER) {
        the_color = 2;
        other_color = 1;
    }
    col++;
    while(col < 8 && Board[row][col].get_color() == the_color) {
        col++;
        flip = true;
    }
    if(col == 8) return false;
    else if(Board[row][col].get_color() == 0) return false;
    else if(flip == true) return true;
}


bool othello::south(string& move) const {
    int row = int(toupper(move[0]) - 'A');
    int col = int(move[1] - '1');
    int the_color, other_color;
    bool flip = false;
    if(game::next_mover() == HUMAN) {
        the_color = 1;
        other_color = 2;
    }
    else if(game::next_mover() == COMPUTER) {
        the_color = 2;
        other_color = 1;
    }
    row++;
    while(col < 8 && Board[row][col].get_color() == the_color) {
        row++;
        flip = true;
    }
    if(row == 8) return false;
    else if(Board[row][col].get_color() == 0) return false;
    else if(flip == true) return true;
}

bool othello::north(string& move) const {
   int row = int(toupper(move[0]) - 'A');
   int col = int(move[1] - '1');
   int the_color, other_color;
   bool flip = false;
   if(game::next_mover() == HUMAN) {
        the_color = 1;
        other_color = 2;
   }
   else if(game::next_mover() == COMPUTER) {
        the_color = 2;
        other_color = 1;
   }
   row--;
   while(row >= 0 && Board[row][col].get_color() == the_color) {
       row--;
       flip = true;
    }
   if(row == -1) return false;
   else if(Board[row][col].get_color() == 0) return false;
   else return flip;

}

bool othello::northwest(string& move) const {
    int row = int(toupper(move[0]) - 'A');
    int col = int(move[1] - '1');
    int the_color, other_color;
    bool flip = false;
    if(game::next_mover() == HUMAN) {
        the_color = 1;
        other_color = 2;
    }
    else if(game::next_mover() == COMPUTER) {
        the_color = 2;
        other_color = 1;
    }
    col--;
    row--;
    while(col >= 0 && row >= 0 && Board[row][col].get_color() == the_color) {
        col--;
        row--;
        flip = true;
    }
    if(col == -1) return false;
    else if(row == -1) return false;
    else if(Board[row][col].get_color() == 0) return false;
    else return flip;
}

bool othello::southwest(string& move) const {
   int row = int(toupper(move[0]) - 'A');
   int col = int(move[1] - '1');
   int the_color, other_color;
   bool flip = false;
   if(game::next_mover() == HUMAN) {
        the_color = 1;
        other_color = 2;
   }
   else if(game::next_mover() == COMPUTER) {
        the_color = 2;
        other_color = 1;
   }
    col--;
    row++;
    while(col >= 0 && row < 8 && Board[row][col].get_color() == the_color) {
        col--;
        row++;
        flip = true;
    }
    if(col == -1) return false;
    else if(row == 8) return false;
    else if(Board[row][col].get_color() == 0) return false;
    else return flip;
}

bool othello::southeast(string& move) const {
   int row = int(toupper(move[0]) - 'A');
   int col = int(move[1] - '1');
   int the_color, other_color;
   bool flip = false;
   if(game::next_mover() == HUMAN) {
        the_color = 1;
        other_color = 2;
   }
   else if(game::next_mover() == COMPUTER) {
        the_color = 2;
        other_color = 1;
   }
    col++;
    row++;
    while(col < 8 && row < 8 && Board[row][col].get_color() == the_color) {
        col++;
        flip = true;
        row++;
    }
    if(col == 8) return false;
    else if(row == 8) return false;
    else if(Board[row][col].get_color() == 0) return false;
    else return flip;
}

bool othello::northeast(string& move) const {
   int row = int(toupper(move[0]) - 'A');
   int col = int(move[1] - '1');
   int the_color, other_color;
   bool flip = false;
   if(game::next_mover() == HUMAN) {
        the_color = 1;
        other_color = 2;
   }
   else if(game::next_mover() == COMPUTER) {
        the_color = 2;
        other_color = 1;
   }
    row--;
    col++;
    while(col < 8 && row >= 0 && Board[row][col].get_color() == the_color) {
        col++;
        row--;
        flip = true;
    }
    if(col == 8) return false;
    else if(row == -1) return false;
    else if(Board[row][col].get_color() == 0) return false;
    else return flip;
}
