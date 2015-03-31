#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include <cstdlib>
#include "Huff.h"
#include "TreeNode.h"
using std::cin;
using std::cout;
using std::vector;
using std::string;
using std::atoi;
using std::endl;
using namespace std;


int main() {
    string filename;
    cin >> filename;
    ifstream fin(filename.c_str());
    if(fin.fail()) {
       cout << "Error in input file.\n";
       return 0;
    }
    string input;
    int length = 0;
    fin >> input;
    if ((input.length()) % 3 != 0) {
        cout << "Error in input file.\n";
        return 0;
    }
    vector<string> theinput;
    theinput.push_back(input);
    length = input.length();
    while (fin >> input) {
        if ((input.length() % 3 != 0) || (input.length() != length)) {
            cout << "Error in input file.\n";
            return 0;
        }
        theinput.push_back(input);
    }
    vector<string> data;
    int data_spot = 0;
    int row, col;
    row = col = 0;
    int number_of_elements = (length * theinput.size()) / 9;
    data.resize(number_of_elements);
    while (row < theinput.size()) {
        while (col < length) {
            for (int i = row; i < row + 3; i++) {
                for (int j = col; j < col + 3; j++) {
                    data[data_spot] += theinput[i][j];
                }
            }
            data_spot++;
            col += 3;
        }
        row += 3;
        col = 0;
    }

    Huff codes;
    codes.set_size(number_of_elements);
    for (size_t i = 0; i < data.size(); i++) {
        codes.insert_element(data[i]);
    }
    codes.build_huff();
    codes.print_tree();
    cout << "compressed file\n";
    size_t counter = 0;
    for( size_t i =0; i < data.size(); i++) {
        codes.compress(data[i]);
        counter++;
        if(counter==length/3) {
           cout << endl;
           counter=0;
        }
    }
}


