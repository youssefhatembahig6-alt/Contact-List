#ifndef AVLTREE_H
#define AVLTREE_H
#include "Contact.h"
#include <iostream>   
#include <string>      
using namespace std;   


class AvlTree {

private:
class  Node { 
    public:
    int height;
    Contact data;  
    Node*   left;
    Node*   right;     
    Node( Contact d)  :height(1), data(d), left(nullptr), right(nullptr) {}
};

     Node* root; 

public:
    AvlTree();                                                        // Done
    ~AvlTree();                                                       // Done
    void  AddContact(const Contact& item);                            // Done
    void  Removecontact(const string name);                           // Done
    Contact  SearchReq(string name);                                  // Done
    void  display();                                                  // Done 


private: 
    void deleteAll(Node*& node);                                       // Done
    void  inorder(Node* node);                                         // Done
    Node* leftRotate(Node * node);                                     // Done
    Node* rightRotate(Node * node);                                    // Done
    int height(Node* n);                                               // Done
    int getBalance(Node* n);                                           // Done
    Node*  insert( Node * node, const Contact& c);                     // Done
    Node*  remove( Node * node, string name );            // use  SearchReqAux to find contact first-------------           
    Contact SearchReqAux(Node *&node, string name);                    // Done
};      
#endif
