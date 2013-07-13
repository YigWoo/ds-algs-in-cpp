#include <string>
#include <vector>
using namespace std;

#ifndef TRIE_H
#define TRIE_H


class Trie {
  public:
    Trie();
    ~Trie();
    size_t size();
    bool isEmpty();
    bool contains(const string& key) const;
    void insert(const string& key);
    void remove(const string& key);
    string longestPrefixOf(string query) const;
    vector<string> keys() const;
    vector<string> keysWithPrefix(const string& key) const;
  public:
    class Node {
    public:
      Node();
      ~Node();
      bool isKey;
      vector<Node*> children;
      /* char c; */
      /* void modChild(int n, Node *child); */
      /* void addChild(Node *child); */
      /* vector<Node*> getChildren(); */
      /* char getChar(); */
      /* void setChar(char c); */
      /* bool getIsKey(); */
      /* void setIsKey(bool b); */
      /* Node* findChild(char c); */
    };
  private:
    const static int R = 26; //26 lowercase english chars
    Node *root;
  private:
    size_t size(const Node* x);
    Trie::Node* put(Node* x, const string& key, size_t d);
    Trie::Node* get(Node* x, const string& key, size_t d) const;
    Trie::Node* remove(Node* x, const string& key, size_t d);
};
#endif
