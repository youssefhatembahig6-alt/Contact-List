#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Contact.h"
#include <iostream>   
#include <string>      
using namespace std;   

struct Node {
    Contact data;  
    Node*   next;  
};

class LinkedList {

private:
    Node* head;   

public:
    LinkedList();    
    LinkedList(const LinkedList& other);        
    LinkedList& operator=(const LinkedList& other); 
    ~LinkedList();   

    void     insert(Contact c);              
    void     deleteByPhone(string phone);
    Contact* searchByPhone(string phone);   
    void     display(ostream& out)const;                       
    bool     isEmpty();  
    int      mySize(); 
 
};
ostream& operator<<(ostream& out, const LinkedList& list);
#endif
