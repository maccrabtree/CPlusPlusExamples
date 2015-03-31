/*
Mac Crabtree
Space Class, for individual spaces on the board
Used in othello.h && othello.cc

The class uses one integer to determine what color the space is,
and this integer can be accessed with get_color(), which returns
the "color" number of that particular space, 0 being empty, 1 being 
white and 2 being black


07/23/2012
*/


#ifndef SPACE
#define SPACE

class space {
   public:
       space() { color = 0;} //defaultly set space to empty
       void flip() {if(color == 1) color = 2; //that is, if it is white
                      else color = 1; } //change to black, or vice versa
       int get_color() const{return color;} //accessor for color getter
       void to_empty() { color = 0;} //changes to empty 
       void to_black() { color = 2;} //changes to black
       void to_white() { color = 1;} //changes to white
       void set_color(int new_color) {color = new_color;}

   private:
       int color; //0 = empty, 1 = white, 2 = black

};

#endif
