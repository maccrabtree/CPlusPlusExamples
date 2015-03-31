/* 
 * File:   TreeNode.cc
 * Mackenzie Crabtree
 * 
 * Contains function definitions for all class definitions 
 * for Huff class. Must include Huff.h
 * 
 * Note to grader/viewer: Some of these functions were derived from
 * skeleton code/algorithms given from Data Structures Using C++ 
 * book by D.S. Malik and from lecture notes given by Dr. Chelberg. 
 */
#include "Huff.h"

//*******************************************************************
//  Function: operator <
//  parameters: TreeNode one and two, which are to be compared
//
//  Description: takes two TreeNodes as parameters, then looks at their
//               freq, and if those are the same, looks at the 'lowest'
//              variable in the tree node class, which contains the integer
//              equivalent of the string name. Function returns true 
//              if node on left hand side of comparison is less than
//              the right hand side.
// Uses: TreeNode functions: get_freq(), get_lowest()
//
// Time: O(1) constant time for constant operations
// Space: O(1) constant space for constant space allocation
//*********************************************************************
bool operator<(TreeNode one, TreeNode two) {
    if (one.get_freq() < two.get_freq()) return true; //lower freq
                                                      //easy less than
    else if (one.get_freq() == two.get_freq()) { //only if freq's are same
        if (one.get_lowest() < two.get_lowest()) {
            return true; //Return true if the lower number is on the left
        }
    }
    return false; //means freq is not lower and 'lowest' is not lower
}

//*******************************************************************
//  Function: top()
//  parameters: none
//
//  Description: simply returns what is on top of the heap
//              which in this case will be the lowest number
//
// Time: O(1) constant time
// Space: O(1) constant space
//*********************************************************************

TreeNode* Huff::top() {
    return heap[1];
}


//*******************************************************************
//  Function: pop()
//  parameters: none
//
//  Description: This function "removes" the top node from the heap,
//               by first swapping it with the last element in the heap,
//               Then, since the heap is broken, it continually swaps
//               the newly swapped element with its lower child (since it is
//               a min heap), until it reaches a good heap state;
// Calls: bad_heap(), heapify() 
// Time: O(logn), where n is the number of 3x3 bits, 
//                since worst case scenario it traverses the tree in a 
//                divided by 2 manner
// Space: O(1) constant space
//*********************************************************************
void Huff::pop() {
    if (heapused == 2) { //Meaning, one element is left
        heapused = 0;    //This is for easy root access, personal choice
        return;
    }
    swap(heap[1], heap[heapused - 1]); //Replace root with the last element
    heapused--; //Essentially delete last element
    size_t heapspot = 1; //start at top (which is newly swapped)
    size_t leftchild = heapspot * 2; //top's left child
    size_t rightchild = leftchild + 1;  //top's right child
    while (bad_heap(heapspot)) {    //checks if the heap is broken
                                    //so while heap is broken, keep sifting
        heapify(leftchild, rightchild, heapspot); //
        leftchild = heapspot * 2;
        rightchild = leftchild + 1;
    }
}

//*******************************************************************
//  Function: bad_heap
//  parameters: heapspot (spot in the heap you are currently at
//
//  Description: The function starts at the spot in the heap given to
//               it by parameter, then compares it with its children
//               (2*n) and (2*n+1), to see if either are lesser, 
//                and since this is a min heap, if either child is lesser
//               the heap is broken. True indiciates broken, false indicates
//               nonbroken heap
// Time: O(1) constant time
// Space: O(1) constant space
//*********************************************************************

bool Huff::bad_heap(size_t heapspot) {
    if ((heapspot * 2 + 1) < heapused) { //Check if right child is in bounds
        if (*heap[heapspot * 2] < *heap[heapspot]) { //if right child is
                                                     //less than parent
                                                     //broken heap
            return true;
        }
        if (*heap[heapspot * 2 + 1] < *heap[heapspot]) { //if left child is
                                                        //less than parent
                                                        //broken heap
            return true;
        }
    } else if (heapspot * 2 < heapused) {    //check if left child is in bounds
        if (*heap[heapspot * 2] < *heap[heapspot]) { //if left child is less
                                                     //than parent
            return true;                             //broken heap
        }
    }
    return false;    //If this executes, heap is ok/inorder/normal/working
}

//*******************************************************************
//  Function: heapify
//  parameters: leftchild index, rightchild index, current spot heapspot
//
//  Description: This function is the bulk of work for the heap restoring
//               . It compares the left child with the right child, determines
//               The lesser, and then swaps that child with the parent. 
//              This function is only called when there is a bad heap
// calls:comparator
// Time: O(1) constant time, doesn't depend on size of anything
// Space: O(1) constant space
//*********************************************************************

void Huff::heapify(size_t& leftchild, size_t& rightchild, size_t& heapspot) {
    if (leftchild < heapused) { //if leftchild index is in bounds of heap
        if (rightchild < heapused) { //if rightchild index is in bounds
            if (*heap[leftchild] < *heap[rightchild]) { //call comparator
                //If the left is lesser, swap current heap with left child
                swap(heap[heapspot], heap[leftchild]);
                heapspot = leftchild; //change the heapspot to where the left
                                        //child was to continue traversal
            } else {
                swap(heap[heapspot], heap[rightchild]); //right must be bigger
                heapspot = rightchild; //swap right with left, right index
            }
        } else {
            swap(heap[heapspot], heap[leftchild]); //if right out of bounds,
            heapspot = leftchild; //Must be left breaking heap, swap and index
        }
    }
}

//*******************************************************************
//  Function: Compress
//  parameters: string to compress "code"
//
//  Description: takes in the string "code" which is what is to be compressed
//               and outputs its corresponding huffman code based on the
//              dictionary entry of its code. Loops through array. 
//
// Time: O(n) where n is the number of unique bits of data, since it
//              traverses an array
// Space: O(1) constant space
//*********************************************************************

void Huff::compress(string code) {
    size_t i = 0;
    while (true) { //Since it must be in the dictionary
        if (dictionary[i].fullcode == code) { //if the code is a match
            cout << dictionary[i].shortcode; //cout corresponding shortened code
            break; //break from loop
        }
        i++; //go to next index
    }
}

//*******************************************************************
//  Function: insert_element
//  parameters: name to insert
// 
//  Description: takes in string from data. If it is unique, it adds it 
//               to the element vector. If it is not, increments frequency
//               of already added string name
//
// Time: O(n) where n is the number of unique elements in the data
// Space: O(1) constant space, since this just adds one everytime.
//              calling it, however, will make it O(n)
//*********************************************************************

void Huff::insert_element(string& name) {
    for (size_t i = 0; i < used; i++) {    //scale through whole list
        if (elements[i].name == name) {   //if the name exists
            elements[i].freq++;            //increment its frequency
            return;
        }
    }
    elements[used].name = name; //This will only execute if unique
    elements[used].lowest = binary(name); //So add it to the elements, and
                                          //store its decimal equiv. number
    used++;     //Increment used 
}


//*******************************************************************
//  Function: set_size
//  parameters: size to be set
//
//  Description:  simply allocates memory for elements array
//
//
// Time: O(1) constant time
// Space: O(n) where n is the size of the data elements coming in
//*********************************************************************
void Huff::set_size(int& size) {
    elements = new TreeNode[size];
}

//*******************************************************************
//  Function: Huff default constructor
//  parameters: none
//
//  Description: sets used to 0, heapused to 1, since it starts at 1, 
//               and index of compression to 0
//
// Time: O(1) constant time
// Space: O(1) constant space
//*********************************************************************

Huff::Huff() {
    used = 0; //For element array
    heapused = 1; //For heap, starts at 1 since heaps start at 1
    index = 0;    //For compression method, starts at zero
}

//*******************************************************************
//  Function: ~Huff (default constructor)
//  parameters:  none
//
//  Description: deallocates allocated memory in Huff class
//
//
// Time: O(1) constant time
// Space: frees up O(n), but takes up O(1) constant space
//*********************************************************************


Huff::~Huff() {
    delete []heap; //deallocate heap's memory
    delete []elements; //deallocate elements memory
    delete []dictionary; //deallocate dictionary memory
}

//*******************************************************************
//  Function: build_huff
//  parameters: none
//
//  Description: Builds huffman Tree. Starts by making heap. 
//               then insert elements into the heap from the elements array
//               Then, as per Huffman algorithm, while the heap has at least
//               two things in it, take them out, make a new node with those
//               two as its children, then put that new node into the heap.
//               Repeat until only one left, which is the root of the huffman
//               tree. 
//
// Time: O(n^2), where n is the size of the unique elements since it must
//                 loop through all of them, then insert into heap, which is
//                  log(n) time. And then each node in the heap is removed
//                  two at a time and put back one at a time, so n operations
//                  again. 
// Space: O(n) Since an array is made, then each two get a new internal node
//               effectively doubling n, but not squaring it. N is the number
//              unique elements
//*********************************************************************

void Huff::build_huff() {
    heap = new TreeNode*[used + 1];
    for (size_t i = 0; i < used; i++) {
        insert_heap(&elements[i]); //Loop through all elements, and add
    }                              //to heap one by one
    
    while (heapused > 0) { //heapused will equal 0 when 1 thing is left
                           //That was programmer's choice of number
        TreeNode* leftchild = top(); //leftchild is smallest freq
        pop();                       //remove smallest
        TreeNode* rightchild = top(); //rightchild is 2nd smallest freq
        pop();                       //remove smallest again
        TreeNode* newnode = new TreeNode;  //make a new, internal node
        newnode->name = "INTERNAL";       //Labeled "internal" for traversal
        newnode->freq = leftchild->freq + rightchild->freq; //add freqs
        newnode->left = leftchild; //set left pointer to left child
        newnode->right = rightchild; //set right pointer to right child
        if (leftchild->lowest < rightchild->lowest) { //Find the lowest binary
            newnode->lowest = leftchild->lowest;   //number between two
        } else {                                  //and set 'lowest' to that
            newnode->lowest = rightchild->lowest; //in new node, for comparison
        }
        insert_heap(newnode); //Insert new node into the heap
    }
    root = heap[0]; //heap[0] will contain the root node (programmer's choice)
    dictionary = new entry[used]; //make a dictionary the size of the unique n
}


//*******************************************************************
//  Function: print_tree
//  parameters: none
//
//  Description: start at root, traverse tree. Call recursive tree traversal
//
//
// Time: O(n) where n is the number of nodes 
// Space: O(1) constant space (assuming stack calls don't count)
//*********************************************************************

void Huff::print_tree() {
    string code = ""; //start it empty
    cout << "dictionary\n";
    print_r_tree(root, code);
}


//*******************************************************************
//  Function: print_r_tree 
//  parameters: TreeNode node, string code
//
//  Description: recursively goes through tree, outputting dictionary code
//               as you go, left is zero, one is right
//              Due to tomfoolery of strings, I had to erase the last
//              character everytime i returned through a function
// Time: O(n) where n is the number of unique elements, 
// Space: O(1), since no new data created as based on calls
//*********************************************************************

void Huff::print_r_tree(TreeNode* node, string code) {
    if (node == NULL) { //Base case
        code.erase(code.length() - 1, code.length());
        return;
    }
    print_r_tree(node->left, code += "0"); //go left, adding zero
    code.erase(code.length() - 1, code.length()); //erase last
    if (node->name != "INTERNAL") {           //dont output internal
        cout << node->name << " " << code << endl; //name follow. by code
        dictionary[index].fullcode = node->name; //set dictionary entry
        dictionary[index].shortcode = code; //to name, with respective code
        index++;                          //increment dictionary index
    }
    print_r_tree(node->right, code += "1"); //go right, increasing 1
    code.erase(code.length() - 1, code.length()); //erase last
    return;
}

//*******************************************************************
//  Function: insert_heap
//  parameters: insert, which is a pointer to a node being inserted
//
//  Description: first, inserts node at end of list, then bubbles that node
//               to the top while it is less than its parent. 
//
// Time: O(logn) where n is the number of unique elements,
//               since it can only swap a number of logn times
// Space: O(1) constant space since it only adds one new node every time
//*********************************************************************

void Huff::insert_heap(TreeNode* insert) {
    heap[heapused] = insert; //add it to end of heap
    if (heapused == 1) { //only one thing in it
        heapused++;    //add to used
        return; //done
    }
    if (heapused == 0) return; 
    size_t temp_key = heapused; //to not lose track of heapused
    while (*heap[temp_key] < *heap[temp_key / 2]) { //while child is less than
        swap(heap[temp_key], heap[temp_key / 2]);   //parent, swap
        temp_key = temp_key / 2;                   //divide to get to new spot
        if (temp_key == 1) break;                  //means at top of heap
    }
    heapused++; //add one to used
}

//*******************************************************************
//  Function: swap
//  parameters: Treenodes to be swapped, treenode one and treenode two
//
//  Description: Simply swaps two treenodes by pointer
//
//
// Time: O(1) constant time
// Space: O(1) constant space
//*********************************************************************


void Huff::swap(TreeNode*& one, TreeNode*& two) {
    TreeNode* temp;
    temp = one;
    one = two;
    two = temp;

}

//*******************************************************************
//  Function: binary
//  parameters: the string to convert
//
//  Description: takes in a string, finds its binary equivalent
//               by traditional base converting algorithm
//
//
// Time: O(1) constant time
// Space: O(1) constant space
//*********************************************************************

int binary(const string convert) {
    int answer = 0; //start at 0
    int power = 8;  //2^8 is the largest power
    for (int i = 0; i < 9; i++) { 
        answer += (convert[i] - 48) * pow(2, power); //48 is the ASCII number
        power--;                                     //for 0, decrement power
    }
    return answer;
}
