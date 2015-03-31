//**********************************************
// Name: Mackenzie Crabtree
// File: Heap.cc
// Created: March 19, 2013
//  
// Description: Contains implementation code for MinHeap project
// for use with Heap.h and included main.cc
//**********************************************

#include "Heap.h"
using namespace std;

//**********************************************
// Function: Heap() default constructor
// Parameters: none
// Calls: none
// Desc: simply sets used to 0, instantiates heap object
// Time: O(1) constant time
// Space: O(1) constant space
//**********************************************


Heap::Heap() {
    used = 0; //heap is empty, so naturally size starts at 0
}


//**********************************************
// Function: print_min()
// Parameters: none
// Calls: none
// Desc: couts min element in heap, or heap at 0.
// Time: O(1) constant time
// Space: O(1) constant space
//**********************************************

void Heap::print_min() {
    cout << heap[0] << endl; //min element will be here (top)
}


//**********************************************
// Function: delete_min()
// Parameters: none
// Calls: bad_heap, heapify
// Desc: Deletes minimum element of heap by first swapping
// last elem. of heap with the first, then popping off the 
// end of the heap, then checks the new head of the heap with its children
// and while the heap property is  broken (aka any child is less than 
// parent, swaps the parent with its least child, and continues to sift down
// Time: O(log3(n)) where n is the number of nodes in the tree
// Space: O(1) constant space
//**********************************************

void Heap::delete_min() {
    swap(heap[0], heap[used - 1]); //move first element to last
    int heapspot = 0;             //start at top of heap
    heap.erase(heap.end() - 1);  //erase last element, (which was first)
    used--;               //decrement used number to reflect one less element
    while (bad_heap(heapspot)) {  //while heap is broken (min not on top)
        int min = heapify(heapspot); //will continually sift down to correct
        heapspot = min;          //heap, and continue sifting.
        if (min == 0) return;    //at the bottom, no need to continue
    }
}

//**********************************************
// Function: is_empty()
// Parameters: none
// Calls: none
// Desc: returns true if heap size is 0, false otherwise
// Time: O(1) constant time
// Space: O(1) constant space
//**********************************************


bool Heap::is_empty() {
    if (used == 0) {     //nothing in list
        return true;     //heap is empty
    }
    return false; //heap is not empty
}


//**********************************************
// Function: insert
// Parameters: integer to_insert
// Calls: none
// Desc: inserts new number into the heap at the bottom, 
//       and while the heap property is broken, (while a parent is
//       greater than its child) swaps the child with the parent and continues
//       to restore the heap property
// Time: O(log3(n)) where n is the number of nodes in the tree
// Space: O(n) where n is one object to be inserted (int in this case)
//**********************************************

void Heap::insert(int& to_insert) {
    heap.push_back(to_insert); //put at end
    if (used == 0) {           //if there was nothing
        used++;                //increase the size, 
        return;                //done with list, 1 element
    }
    int parent = (used - 1) / 3; //find parent of newly inserted item
    int temp_used = used; //to not lose used
    while (heap[parent] > heap[temp_used]) { //if the parent
        swap(heap[parent], heap[temp_used]); //is larger than the child
        temp_used = parent; //swap them, and keep going
        parent = (parent - 1) / 3; //find parent of new heap spot
    }
    used++; //increment size of heap to reflect new element
}

//**********************************************
// Function: bad_heap()
// Parameters: heapspot index
// Calls: none
// Desc: takes in an index in the heap, and checks this index with its
//       three children and returns true if any of the children are less
//       than its parent, meaning the heap property is broken
// Time: O(1) constant time
// Space: O(1) constant space
//**********************************************



bool Heap::bad_heap(int heapspot) {
    if (heapspot * 3 + 1 < used) {
        if (heap[heapspot * 3 + 1] < heap[heapspot]) {
            return true;
        } else if (heapspot * 3 + 2 < used) {
            if (heap[heapspot * 3 + 2] < heap[heapspot]) {
                return true;
            } else if (heapspot * 3 + 3 < used) {
                if (heap[heapspot * 3 + 3] < heap[heapspot]) {
                    return true;
                }
            }
        }
    }
    return false;
}

//**********************************************
// Function: Heapify
// Parameters: heapspot index
// Calls: swap
// Desc: takes in index of current heapspot, calculates its left, mid, and
// right children, then finds the smallest child out of all of them,
// and swaps the parent with its least child, and returns the index of the 
// smallest child (which is now the current index)
// Time: O(1) constant time
// Space: O(1) constant space
//**********************************************


int Heap::heapify(int heapspot) {
    //First, find minimum child
    int leftchild, midchild, rightchild;
    leftchild = heapspot * 3 + 1; //leftchild of current element
    midchild = heapspot * 3 + 2; //midchild of current element
    rightchild = heapspot * 3 + 3; //rightchild of current element
    int min; //will hold index of lowest element
    if (leftchild < used) {
        min = leftchild;
        if (midchild < used) {
            if (heap[midchild] < heap[min]) {
                min = midchild;
            }
            if (rightchild < used) {
                if (heap[rightchild] < heap[min]) {
                    min = rightchild;
                } //end if
            }  //end rightchild < used
        }      //end midchild < used
    }   //end leftchild < used

    //Swap lowest child with parent
    swap(heap[heapspot], heap[min]);
    return min; //return index of lowest element

}
