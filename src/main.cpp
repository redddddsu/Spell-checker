#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include "../header/linkedlist.hpp"

using namespace std;

int main() {
    string word;

    cout << "Enter word" << endl;
    cin >> word;

    ifstream file;
    file.open("dict/dictionary.txt");
    
    if(!(file.is_open()))
        throw runtime_error("Bad");
    
    string newWord = "world";
    string editedWord;
    string editedNewWord;

    int steps = 0;
    int top;
    int left;
    int diagonal;
    int minimum;
    int row ;
    int col;
    string c;
    int counter;

    linkedlist list;
    
    while (file >> newWord) {

        if (word == newWord) {
            return 0;
        }

        /*
        Given how people wil mostly like type the first letter correctly
        we can just if the first character is equal.
        If not we just continue
        */
        if (word[0] != newWord[0]) {
            continue;
        }

        editedWord = word;
        editedNewWord = newWord;

        //need to add an empty space in the begin for the algorithm to work
        //also as an indicator when to stop

        //row
        editedWord = editedWord.insert(0, " ");

        //column
        editedNewWord.insert(0, " ");

        int matrix[editedWord.size()][editedNewWord.size()];


        //[0][0] will always be zero
        matrix[0][0] = 0;


        // for (int i = 0; i < editedWord.size(); i++) {
        //     for (int j = 0; j < editedNewWord.size(); j++) {
        //         matrix[i][j] = 0;
        //     }
        // }

        //the first row and column will just be incrementing
        for (int i = 1; i < editedNewWord.size(); i++) {
            matrix[0][i] = i;
        }

        for (int i = 1; i < editedWord.size(); i++) {
            matrix[i][0] = i;
        }
        
        /*
        insert every other item by using this algorithm
        find the minimum between the number to its left, the number on top of, and the number diagonal to the top left
        
        x x ! ! x x
        x x ! ? x x
        x x x x x x
        x x x x x x
        x x x x x x
        
        x = don't care
        ? = number we want to insert
        ! = the minimum of those numbers

        when we find the minimum of !, insert into ?

        if the char at column doesn't matches with the char at the row
        we add one
        */ 
        for (int i = 1; i < editedWord.size(); i++) {    
            for (int j = 1; j < editedNewWord.size(); j++) {
                matrix[i][j] = min({matrix[i-1][j-1], matrix[i-1][j], matrix[i][j-1]});
                if (editedWord[i] != editedNewWord[j]) {
                    matrix[i][j] += 1;
                }
            }
        }

        /*
        now for the actual "text changing"
        start from bottom corner
        we can move, left, up, or diagonal

        moving up deletes
        moving left inserts
        moving diagonal replace

        but if the smallest is the same, we do nothing
        */
        steps = 0;
        top;
        left;
        diagonal;
        minimum;
        row = editedWord.size() - 1;
        col = editedNewWord.size() - 1;
        counter = matrix[row][col];



        while(matrix[row][col] !=  0) {
            /*
            Due to the two words having different size
            We need to check if row or col is equal to zero
            because it can cause of out range.
            If they are equal to zero we just break the loop and say that 
            no words are equivalent.
            */
            if (row == -1 || col == -1) {
                break;
            }

            diagonal = matrix[row - 1][col - 1];
            left = matrix[row][col - 1];
            top = matrix[row - 1][col];

            minimum = min({matrix[row-1][col-1], matrix[row-1][col], matrix[row][col-1]});
            

            if (counter > minimum) {        
                if (top == minimum) {
                    editedWord.erase(row, 1);
                    row--;   
            }
            else if (left == minimum) {
                c = editedNewWord[col];
                editedWord.insert(row + 1, c);
                col--;
            }
            else {
                c = editedNewWord[col];
                editedWord.replace(row, 1, c);
                row--;
                col--;
            }
            counter--;
            steps++;
            }
            else if (counter == diagonal) {
                row--;
                col--;
            }
            else if (counter == left)
                row--;
            else 
                col--;
        }


        if (newWord == editedWord.erase(0, 1)) {
            list.push(newWord, steps);
        }
        steps = 0;
    }
    
    list.printSmallestStep();


    return 0;
}

