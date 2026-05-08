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
    AvlTree();                                                        
    ~AvlTree();                                                       
    bool    AddContact(const Contact& item);        
    void    RemoveContact(const string& name);      
    void    UpdateContact(const string& name);      
    Contact SearchReq(const string& name);                                
    void  display();
                                                  

private: 
   void    deleteAll(Node*& node);
    void    inorder(Node* node);
    Node*   leftRotate(Node* node);
    Node*   rightRotate(Node* node);
    int     height(Node* n);
    int     getBalance(Node* n);
    Node*   insert(Node* node, const Contact& c);
    Node*   remove(Node* node, const string& name);
    Contact SearchReqAux(Node* node, const string& name);
    bool searchByPhone(Node* node, const string& phone);
};
#endif
