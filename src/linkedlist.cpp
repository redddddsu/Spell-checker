#include "../header/linkedlist.hpp"

using namespace std;

/*
Simple linkedlist implementation with delete constructor and only push
*/

linkedlist::linkedlist() {
    head = nullptr;
    tail = nullptr;
}

void linkedlist::push(string word, int steps) {
    Node * newNode = new Node(word, steps);
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }

}

void linkedlist::printSmallestStep() {
    Node * temp = head;

    //We first need to find the smallest step in list
    int smallestStep = temp->steps;
    while (temp) {
        if (smallestStep > temp->steps)
            smallestStep = temp->steps;
        temp = temp->next;
    }

    temp = head;
    cout << endl;

    //Print the smallest step
    while (temp) {
        if (smallestStep == temp->steps)
            cout << temp->word << endl;
        temp = temp->next;
    }
}

linkedlist::~linkedlist() {
    while (head) {
        Node * temp = head->next;
        delete head;
        head = temp;
    }
}

