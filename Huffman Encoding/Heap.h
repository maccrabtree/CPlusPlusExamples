//*******************************************************************
// Name: Mackenzie Crabtree
// File: Heap.h
//       Contains class declarations and member functions
//       for min heap class
// Created Mar 18, 2013
//*******************************************************************

#include <iostream>
#include <vector>
using namespace std;
#ifndef HEAP_H
#define HEAP_H

class Heap {
public:

    //*****************************************
    // Function: Heap()
    // default constructor
    // Desc: Sets size to 0, instantiates object
    // Time: O(1) constant time
    // Space: O(1) constant space
    //*****************************************
    Heap();
    
    //************************************************************
    //Function: insert
    //Desc: inserts a new element into the heap into the
    //      appropriate place
    //Time: O(log3(n)) where n is the number of nodes in the tree
    //Space: O(1) constant space, constant memory allocated per call
    //************************************************************
    void insert(int& to_insert);
    
    //*************************************************************
    //Function: delete_min()
    //Desc: Removes top element (aka minimum element) from the heap
    //Time: O(log3(n)) where n is the number of nodes in the tree
    //Space: O(1) constant space, no new memory allocated
    void delete_min();
    
    //*************************************************************
    //Function: print_min()
    //Desc: prints the minimum (or top) element of the heap
    //Time: O(1) constant time
    //Space: O(1) constant space
    //*************************************************************
    void print_min();
    
    //************************************************************
    //Function: is_empty()
    //Desc: returns true if the heap is empty (size 0), false otherwise
    //Time: O(1) constant time
    //Time: O(1) constant space
    //*************************************************************
    bool is_empty();
    
    
private:
    
    //*************************************************************
    //Function: heapify
    //Desc: starts with given index, and sifts current node or data
    //      down with its lowest child until its in the correct place in heap
    //Time: O(log3(n)) where n is the number of nodes in the heap
    //Space: O(1) constant space
    int heapify(int heapspot);
    
    //Function: bad_heap
    //Desc: Checks current given index with all of its children and returns true
    //      if any of the children are less than its parent
    bool bad_heap(int heapspot);
    
    vector<int> heap; //will contain the whole heap
    int used;         //simply an extra variable to keep track of used so 
                      //I won't have to use heap.size() everytime




};
#endif //HEAP_H
