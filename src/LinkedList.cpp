#include "LinkedList.h"
// LinkedList implementation

LinkedList::LinkedList():head(nullptr) {}
    

LinkedList::LinkedList(const LinkedList& other):head(nullptr) {

    Node* current = other.head;
    while (current != nullptr) {
        insert(current->data);
        current = current->next;
    }
}


LinkedList& LinkedList::operator=(const LinkedList& other) {

    if (this == &other) {
        return *this;
    }
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current;
        current    = current->next;
        delete temp;
    }
    head = nullptr;
    current = other.head;
    while (current != nullptr) {
        insert(current->data);
        current = current->next;
    }
    return *this;
}


LinkedList::~LinkedList() {
    Node* current = head;

    while (current != nullptr) {
        Node* temp = current;
        current    = current->next;
        delete temp;
    }
    head = nullptr;
}


bool LinkedList::isEmpty() {
    return head == nullptr;
}


void LinkedList::insert(Contact c) {

    Node* newNode  = new Node();
    newNode->data  = c;
    newNode->next  = nullptr;
    if (isEmpty()) {
        head = newNode;
        return;
    }
    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = newNode;
}


Contact* LinkedList::searchByPhone(string phone) {

    Node* current = head;
    while (current != nullptr) {
        if (current->data.phone == phone) {
            return &(current->data);
        }
        current = current->next;
    }
    return nullptr;
}


void LinkedList::deleteByPhone(string phone) {
 
    if (isEmpty())
        return;
    if (head->data.phone == phone) {
        Node* temp = head;
        head       = head->next;
        delete temp;
        return;
    }
    Node* prev    = head;
    Node* current = head->next;
    while (current != nullptr) {
        if (current->data.phone == phone) {
            prev->next = current->next;
            delete current;
            return;
        }
        prev    = current;
        current = current->next;
    }
}


int LinkedList::mySize() {

    int   count   = 0;
    Node* current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}


void LinkedList::display(ostream& out) const {

    if (head == nullptr) {
        out << "No contacts in the list.\n";
        return;
    }
    Node* current = head;
    int   count   = 1;
    while (current != nullptr) {
        out << "[" << count << "]\n"
            << "  Name    : " << current->data.name    << "\n"
            << "  Phone   : " << current->data.phone   << "\n"
            << "  Email   : " << current->data.email   << "\n"
            << "  Address : " << current->data.address << "\n"
            << "-----------------------------\n";
        current = current->next;
        count++;
    }
}


ostream& operator<<(ostream& out, const LinkedList& list) {
    list.display(out);
    return out;
}
