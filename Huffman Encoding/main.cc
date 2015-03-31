//***************************************************
//File: main.cc
//Name: Mackenzie Crabtree
//      main program for min heap project, contains "menu"esque
//      input system
//
// Created: march 18, 2013
//


#include <iostream>
#include <cstdlib>
#include "Heap.h"
using namespace std;




int main() {
  cout << "Ternary Heap Program\n";
  cout << "\tPress I and an integer to insert into\n";
  cout << "\tPress P to print min element in current heap\n";
  cout << "\tPress D to delete top element from heap\n";
  cout << "\tPress Q to Quit Program\n";
  char option; //Option for later switch choice
  cin >> option; //get first character, prime the loop
  Heap heap;    //make instance of heap

  while(option != 'Q') {   //Q signifies end
    switch(option) {
       case 'I':    //INSERT
	  int read_in; //integer to inssert
	  cin >> read_in; //read it in
	  if(cin.fail()) {
	    cin.clear();
	    break;
          }
	  heap.insert(read_in); //insert it into heap
          break;
       
       case 'D':   //DELETE
          if(heap.is_empty()) { 
            cout << "Heap empty\n";
	    break;
          }
	  heap.delete_min(); 
	  break;

       case 'P':   //PRINT MINIMUM
          if(heap.is_empty()) {
            cout << "Heap empty\n";
            break;
          }
	  heap.print_min();
	  break;
       case 'Q':  //QUIT
	  break;
       default:    //INVALID LETTER/CHOICE
	  cout << "invalid command\n";
	  break;
     }
    
    cin >> option; //get next option
    if(cin.eof()) {
      return 0;
    }
  }
}
