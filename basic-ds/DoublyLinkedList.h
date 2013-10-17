#ifndef _DOUBLY_LINKED_LIST_H
#define _DOUBLY_LINKED_LIST_H
#include <cstdlib>
template <typename Object>
class DoublyLinkedList {
  private:
    struct Node {
        Object data;
        Node *prev;
        Node *next;
        Node(const Object &obj = Object(),
             Node *p = NULL,
             Node *n = NULL) : data(obj), prev(p), next(n) {}
    };
    
  public:
    class const_iterator {
      protected:
        Node* current;
        Object& retrieve() const {return current->data;}
        const_iterator(Node *p) : current(p) {}
        friend class DoublyLinkedList<Object>;
      public:
        const_iterator() : current(NULL) {}
        const Object& operator* () const {return retrieve();}
        const_iterator& operator++ () {
            current = current->next;
            return *this;
        }
        const_iterator operator++ (int) {
            const_iterator old = *this; // can it compile?
            //it can compile, but the return variable should be a value
            ++(*this);
            return old;
        }
        const_iterator& operator-- () {
            current = current->prev;
            return *this;
        }
        const_iterator operator-- (int) {
            const_iterator old = *this;
            --(*this);
            return old;
        }
        bool operator== (const const_iterator& rhs) {
            return current == rhs.current;
        }
        bool operator!= (const const_iterator& rhs) {
            return !(*this == rhs);
        }
    };

    class iterator : public const_iterator {
      protected:
        iterator(Node *p) : const_iterator(p) {}
        friend class DoublyLinkedList<Object>;
      public:
        iterator() {}
        Object& operator* () {return const_iterator::retrieve();}
        const Object& operator* () const {
            return const_iterator::operator*();
        }
        iterator& operator++() {
            const_iterator::current = const_iterator::current->next;
            return *this;
        }
        iterator& operator++(int) {
            iterator old = *this;
            ++(*this);
            return old;
        }
        iterator& operator--() {
            const_iterator::current = const_iterator::current->prev;
            return *this;
        }
        iterator& operator--(int) {
            iterator old = *this;
            --(*this);
            return old;
        }
    };

  public:
    DoublyLinkedList() {init();}
    ~DoublyLinkedList() {
        clear();
        delete head;
        delete tail;
    }
    DoublyLinkedList(const DoublyLinkedList &rhs) {
        init();
        *this = rhs;
    }
    const DoublyLinkedList& operator= (const DoublyLinkedList &rhs) {
        if (this == &rhs)
            return *this;
        clear();
        for (const_iterator iter = rhs.begin(); iter != rhs.end();  ++iter) {
            push_back(*iter);
        }
        return *this;
    }
    iterator begin() {return iterator(head->next);}
    iterator end() {return iterator(tail);}
    // if you declare the constness of a function, it could be overloaded
    const_iterator begin() const {return const_iterator(head->next);} 
    const_iterator end() const {return const_iterator(tail);}
    int size() {return sz;}
    bool empty() {return size() == 0;}
    void clear() {
        while(!empty()) {
            pop_front();
        }
    }
    Object& front() {return *begin();}
    Object& back() {return *--end();}
    const Object& front() const {return *begin();}
    const Object& back() const {return *--end();}
    void push_front(const Object &obj) {
        insert(begin(), obj);
    }
    void push_back(const Object &obj) {
        insert(end(), obj);
    }
    void pop_front() {
        erase(begin());
    }
    void pop_back() {
        erase(--end());
    }
    iterator insert(iterator iter, const Object &obj) {
        Node *p = iter.current;
        Node *pPrev = p->prev;
        Node *newNode = new Node(obj, pPrev, p);
        pPrev->next = newNode;
        p->prev = newNode;
        ++sz;
        return iterator(newNode);
    }
    iterator erase(iterator iter) {
        Node *p = iter.current;
        Node *pPrev = p->prev;
        Node *pNext = p->next;
        pPrev->next = pNext;
        pNext->prev = pPrev;
        delete p;
        --sz;
        return iterator(pNext);
    }
    
  private:
    // member variable name conflicts with member function name!
    // if you declare 'int size', it conflicts with 'int size()'
    // watch out.
    int sz;
    Node *head;
    Node *tail;
    void init() {
        sz = 0;
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->prev = head;
    }
};
#endif
