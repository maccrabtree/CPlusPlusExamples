/* 
 * File:   Huff.h
 * Author: Mackenzie Crabtree
 *
 * Contains class Huff declarations, along with an accompanying binary function
 * For use with Huff.cc
 * Created on February 21, 2013, 10:05 PM
 */

#ifndef HUFF_H
#define	HUFF_H
#include <iostream>
#include <cstdlib>
#include <queue>
#include <cmath>
#include <vector>
#include "TreeNode.h"
using std::string;


struct entry {
   string fullcode; //or Full string
   string shortcode; //or Huff code
};

//************************************************
//Name: binary
//Desc: returns integer equivalent of binary string
//      num
//Time: O(1) constant time
//Space: O(1) constant time
//************************************************
int binary(const string convert);


class Huff {
public:

//***********************************************
//Name: Huff(), default constructor
//Desc:  sets indeces to proper numbers
//Time: O(1) const
//Space: O(1) const
//************************************************
    Huff();

//************************************************
//Name: ~Huff(), deconstructor
//Desc: deallocates memory used in class
//Time: O(1) constant time 
//Space: O(1) constant space, but frees up O(n)
//************************************************
    ~Huff();

//************************************************
//Name: insert_element
//Params: string name to be inserted
//Desc: inserts element to array, and increases 
//      frequency of ones already added
//Time: O(n) where n is the number of 3x3 in
//           the data
//Space: O(n) where n is the number of 3x3 in data
//************************************************
    void insert_element(std::string& name);

//************************************************
//Name: set_size
//Params: size of elements
//Desc: simply makes array of needed size
//Time: O(1)
//Space: O(n) where n is the number of 3x3 in data
//************************************************
    void set_size(int& size);


//************************************************
//Name: build_huff
//Desc: builds the huffman tree of codes to be used
//Time: O(nlogn) where n is the number of 3x3 in the
//	 	 data
//Space: O(n) where n is the number of 3x3 in the data
//************************************************
    void build_huff();

//************************************************
//Name: insert_heap
//params:TreeNode to insert into heap
//Desc: Inserts the given TreeNode pointer to its
//	correct place in the heap
//Time: O(logn) where n is the number of 3x3
//Space: O(1) since only one new spot is being created
//************************************************
    void insert_heap(TreeNode* insert);

//************************************************
//Name: print_tree
//Desc: Calls printing tree function, prints huffman
//      tree and builds dictionary
//Time: O(n) where n is the number of unique 3x3
//Space: O(1) since no new data is created
//************************************************
    void print_tree();

    entry* dictionary; //holds all huffman codes
			//with corres. long codes

//************************************************
//Name: print_r_tree
//Desc: recursive call for printing tree, traverses
//      and prints whole tree
//Time: O(n) where n is the number of unique 3x3
//Space: O(1) since no new data is being created
//************************************************
    void print_r_tree(TreeNode* node, std::string code);

//************************************************
//Name: compress
//Desc: takes in string, outputs the shortened string
//	from "dictionary" previously made
//Time: O(n) where n is the number of unique 3x3
//Space: O(1) since data created is constant
//************************************************
    void compress(string code);
private:
    TreeNode* elements; //Array of unique elements
    TreeNode** heap;    //To be max heap (of node pointers)


//************************************************
//Name: bad_heap
//Desc: Returns true if heap is broken, meaning
//      elements in heap are out of order
//Time: O(1) constant time
//Space: O(1) constant space
//************************************************
    bool bad_heap(size_t heapspot);

//************************************************
//Name: top()
//Desc: returns top element of min heap
//Time: O(1) constant time
//Space: O(1) constant space
//************************************************
    TreeNode* top();

//************************************************
//Name: pop()
//Desc: removes minimum element from min heap, rea
//      adjusts heap to be perfect again
//Time: O(logn) where n is the number of Unique 3x3
//Space: O(1) since no new data is created
//************************************************
    void pop();

//************************************************
//Name: heapify
//Desc: readjusts the heap to make it perfect again
//Time: O(logn) where n is the number of unique 3x3
//Space: O(1) constant space
//************************************************

    void heapify(size_t& leftchild, size_t& rightchild, size_t& heapspot);

//************************************************
//Name: swap
//Desc: Swaps the two treenodes given
//Time: O(1) constant time
//Space: O(1) constant space
//************************************************
    void swap(TreeNode*& one, TreeNode*& two);

    TreeNode* root; //Root of the huffman tree
    size_t used;    //Used for element array
    size_t heapused; //used for heap array
    size_t index;    //used for dictionary array
};

#endif	/* HUFF_H */

