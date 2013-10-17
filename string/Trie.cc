#include "Trie.h"
#include <iostream>
using namespace std;

Trie::Node::Node():isKey(false) {
    for (int i = 0; i < R; i++)
        children.push_back(NULL);
}
Trie::Node::~Node() {}
/* void Trie::Node::modChild(int n, Node *child) { */
/*   if (n < children.size()) */
/*     children[n] = child; */
/*   else */
/*     cout << "wrong index" << endl; */
/* } */
/* vector<Trie::Node*> Trie::Node::getChildren() {return children;} */
/* void Trie::Node::addChild(Node *child) {children.push_back(child);} */
/* char Trie::Node::getChar() {return content;} */
/* void Trie::Node::setChar(char c) {content = c;} */
/* bool Trie::Node::getIsKey() {return isKey;} */
/* void Trie::Node::setIsKey(bool b) {isKey = b;} */
/* Trie::Node* Trie::Node::findChild(char c) { */
/*   for (size_t i = 0; i != children.size(); i++) { */
/*     Node *tmp = children[i]; */
/*     // if tmp != NULL is not added, there will be a bug */
/*     //  since addChild do not check for NULL nodes */
/*     //  if we add NULL node into children */
/*     //  and call findChild, NULL node will be used */
/*     //  cause NULL pointer exceptions */
/*     if (tmp != NULL && tmp->getChar() == c) */
/*       return tmp; */
/*   } */
/*   return NULL; */
/* } */

Trie::Trie() { root = new Node();}
Trie::~Trie() {
    destory(root);
}
void Trie::destory(Node* x) {
    for (int i = 0; i < R; i++)
        if (x->children[i] != NULL)
            destory(x->children[i]);
    delete x;
}
size_t Trie::size() {return size(root);}
size_t Trie::size(const Node* x) {
    if (x == NULL) return 0;
    size_t cnt = 0;
    if (x->isKey == true) cnt++;
    for (int i = 0; i < R; i++)
        cnt += size(x->children[i]);
    return cnt;
}
bool Trie::isEmpty() {return size(root) == 0;}
void Trie::insert(const string& key) {
    root = put(root, key, 0);
}
Trie::Node* Trie::put(Node* x, const string& key, size_t d) {
    if (x == NULL) x = new Node();
    if (d == key.length()) {
        x->isKey = true;
        return x;
    }
    char c = key[d];
    x->children[c-'a'] = put(x->children[c-'a'], key, d+1);
    return x;
}
bool Trie::contains(const string& key) const{
    /* const pointer as return type */
    const Node* x = get(root, key, 0);
    if (x == NULL) return false;
    return x->isKey;
}
const Trie::Node* Trie::get(Node* x, const string& key, size_t d) const {
    if (x == NULL) return NULL;
    if (d == key.size()) return x;
    char c = key[d];
    /* the next line is a little bit of hard coding */
    /* some other lines in the code are similar */
    return get(x->children[c-'a'], key, d+1);
}
void Trie::remove(const string& key) {
    root = remove(root, key, 0);
}
Trie::Node* Trie::remove(Node* x, const string& key, size_t d) {
    if (x == NULL) return NULL;
    if (d == key.size()) x->isKey = false;
    else {
        char c = key[d];
        x->children[c-'a'] = remove(x->children[c-'a'], key, d+1);
    }
    /*   The following line is a tricky line,
     * it ensures that if the node corresponds
     * to the last character of a key, recursive
     * deletion stops here, otherwise,  program
     * check whether the node has non-NULL nodes,
     * if not, it will remove current node.
     */
    if (x->isKey != false) return x;
    for (int c = 0; c < R; c++)
        if (x->children[c] != NULL)
            return x;
    delete x;
    return NULL;
}
string Trie::longestPrefixOf(string query) const {
}
vector<string> Trie::keys() const {
    return keysWithPrefix("");
}
vector<string> Trie::keysWithPrefix(const string& prefix) const {
    vector<string> q;
    collect(get(root, prefix, 0), prefix, q);
    return q;
}
void Trie::collect(const Node* x, const string& key, vector<string>& q) const {
    if (x == NULL) return;
    if (x->isKey == true) q.push_back(key);
    for (int i = 0; i < R; i++) {
        char c = (char) (i + 'a');
        collect(x->children[i], key+c, q);
    }
}
/* unit test */
int main() {
    /* Trie::Node *root = new Trie::Node(); */
    /* for (int i = 0; i < 26; i++) */
    /*   root->addChild(NULL); */
    /* root->setChar('a'); */
    /* root->setIsKey(true); */

    /* Trie::Node *child = new Trie::Node(); */
    /* child->setChar('b'); */
    /* child->setIsKey(true); */
    /* for (int i = 0; i < 26; i++) */
    /*   child->addChild(NULL); */

    /* root->modChild('b'-'a', child); */
    /* vector<Trie::Node*> children = root->getChildren(); */
    /* for (int i = 0; i < 26; i++) */
    /*   if (children[i] != NULL) */
    /*     cout << children[i]->getChar() << endl; */
    /* cout << root->findChild('b')->getChar() << endl; */
    Trie trie = Trie();
    cout << trie.size() << endl;
    if (trie.isEmpty())
        cout << "The trie is empty" << endl;
    trie.insert("she");
    trie.insert("sells");
    trie.insert("sea");
    trie.insert("shells");
    trie.insert("by");
    trie.insert("the");
    trie.insert("sea");
    trie.insert("shore");
    vector<string> vs;
    vs = trie.keys();
    for (vector<string>::iterator it = vs.begin(); it != vs.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
    cout << "The size of the trie is: ";
    cout << trie.size() << endl;
    if (trie.contains("sea"))
        cout << "trie contains sea" << endl;
    if (!trie.contains("shell"))
        cout << "trie doesn't contains shell" << endl;
    trie.remove("sea");
    trie.remove("by");
    trie.remove("sells");
    trie.remove("she");
    cout << "The size of the trie is: ";
    cout << trie.size() << endl;
    cout << trie.contains("shells") << endl;
    cout << trie.contains("she") << endl;
    trie.insert("she");
    cout << trie.contains("she") << endl;
    trie.remove("sh");
    trie.remove("hah");
    cout << trie.size() << endl;
}
