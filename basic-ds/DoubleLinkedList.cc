#include "DoubleLinkedList.h"
#include <iostream>
using namespace std;

int main() {
    DoubleLinkedList<int> intlist;
    for (int i = 0; i < 5; i++) {
        intlist.push_front(i);
        intlist.push_back(i);
    }
    cout << "front: " << intlist.front() << endl;
    cout << "back: " << intlist.back() << endl;
    cout << "size: " << intlist.size() << endl;
    for (DoubleLinkedList<int>::const_iterator iter = intlist.begin();
         iter != intlist.end();
         iter++) {
        cout << *iter << " ";
    }
    cout << endl;
    for (DoubleLinkedList<int>::iterator iter = intlist.begin();
         iter != intlist.end();
         ++iter) {
        *iter = 10;
    }
    for (DoubleLinkedList<int>::const_iterator iter = intlist.begin();
         iter != intlist.end();
         iter++) {
        cout << *iter << " ";
    }
    cout << endl;
    DoubleLinkedList<int> intlist2;
    for (int i = 0; i < 10; i++) {
        intlist2.push_front(i);
    }
    intlist = intlist2;
    for (DoubleLinkedList<int>::const_iterator iter = intlist.begin();
         iter != intlist.end();
         iter++) {
        cout << *iter << " ";
    }
}
