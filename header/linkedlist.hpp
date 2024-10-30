#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <iostream>

using namespace std;

struct Node {
    string word;
    int steps;
    Node *next;
    Node(string w, int s) : word(w), steps(s), next(nullptr) { }
};

class linkedlist {
    private:
        Node * head;
        Node * tail;
    public:
        linkedlist();
        ~linkedlist();
        void push(string, int);
        void printSmallestStep();
};

#endif