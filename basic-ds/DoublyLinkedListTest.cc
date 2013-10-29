#include "DoublyLinkedList.h"
#include <iostream>
using namespace std;

int main() {
    DoublyLinkedList<int> intlist;
    for (int i = 0; i < 5; i++) {
        intlist.push_front(i);
        intlist.push_back(i);
    }
    cout << "From intlist: " << endl;
    cout << "front: " << intlist.front() << endl;
    cout << "back: " << intlist.back() << endl;
    cout << "size: " << intlist.size() << endl;
    DoublyLinkedList<int>::const_iterator constIter;
    printTheList(intlist, constIter);
    cout << "intlist all set to 10" << endl;
    for (DoublyLinkedList<int>::iterator iter = intlist.begin();
         iter != intlist.end();
         ++iter) {
        *iter = 10;
    }
    printTheList(intlist, constIter);
    DoublyLinkedList<int> intlist2;
    cout << "From intlist2: " << endl;
    for (int i = 0; i < 10; i++) {
        intlist2.push_front(i);
    }
    printTheList(intlist2, constIter);
    cout << "assign: intlist = intlist2" << endl;
    intlist = intlist2;
    cout << "From intlist: " << endl;
    printTheList(intlist, constIter);
}

