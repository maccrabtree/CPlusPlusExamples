/* 
 * File:   TreeNode.h
 * Author: Mackenzie Crabtree
 * Desc: contains function definitions and
// Class necessities for TreeNode class.
// For use with TreeNode.cc
// 
// NOTE: I APOLOGIZE FOR INLINE FUNCTIONS
//      THEY MADE COMPILING EASIER, AND 
//      ARE VERY SIMPLE
 */

#ifndef TREENODE_H
#define	TREENODE_H
#include <string>
#include <cstdlib>
using namespace std;


class TreeNode {
    friend class Huff;
public:
//************************************************
//Name: TreeNode()
//Desc: Default constructor, initializes freq to 0
//      and children to NULL
//Time: O(1) constant
//Space: O(1) constant
//************************************************
    TreeNode();

//************************************************
//Name: get_freq
//Desc: simply returns frequency variable
//Time: O(1) constant time
//Space: O(1) constant space;
//************************************************
    int get_freq() const {return freq;}

//************************************************
//Name: get_name
//Desc: Simply returns name variable
//Time: O(1) constant
//Space: O(1) constant
//************************************************
    string get_name() const {return name;}

//************************************************
//Name: get_lowest
//Desc: Simply returns lowest variable
//Time: O(1) constant
//Space: O(1) constant
//************************************************
    int get_lowest() { return lowest;}

//************************************************
//Name: get_left
//Desc: Simply returns leftchild of node
//Time: O(1) constant time 
//Space: O(1) constant space
//************************************************
    TreeNode* get_left() {return left;}

//**********************************************
//Name: get_right
//Desc: Simply returns rightchild of node
//Time: O(1) constant
//Space: O(1) constant
//************************************************
    TreeNode* get_right() {return right;}
private:
    int freq; //frequency of current element
    string name; //name, in binary
    int lowest; //stores number of lowest string name value of children
    TreeNode* left; //left child pointer
    TreeNode* right; //right child pointer
    
};

#endif	/* TREENODE_H */

