============================================================
           Contact Management System
============================================================

PROJECT DESCRIPTION
------------------------------------------------------------
A console-based Contact Management System implemented in C++
using core data structures. The system allows users to add,
search, update, delete, and list contacts efficiently.
Built as a group project for CSE333 - Data Structures and
Algorithms, Spring 2026.


DATA STRUCTURES USED
------------------------------------------------------------

1. Singly Linked List
   - Used as the primary storage structure for all contacts.
   - Allows insertion at the end by traversing to the last node in O(n)
   - Allows deletion using two pointers (prev + current) in O(n)
   - Since all phone-based operations require traversal anyway,
     a singly linked list is sufficient and simpler to implement
   - Reflects the List chapter covered in the course (Ch02 / Ch05)

2. Binary Search Tree (BST)
   - Used to index all contacts by name for fast retrieval and sorted output.
   - Supports name-based search in O(log n) average case
   - In-order traversal automatically produces alphabetically sorted list
   - Reflects the Trees chapter covered in the course (Ch06)


FEATURES
------------------------------------------------------------
1. Add a new contact (name, phone number, email, address)
2. Search contact by name using BST        - O(log n)
3. Search contact by phone using Linked List - O(n)
4. Update an existing contact's information
5. Delete a contact from both the list and the BST
6. Display all contacts in alphabetical order via BST in-order traversal


TIME COMPLEXITY SUMMARY
------------------------------------------------------------
Operation               Data Structure          Complexity
---------               --------------          ----------
Add contact             Linked List + BST       O(log n)
Search by name          BST                     O(log n)
Search by phone         Linked List             O(n)
Delete contact          BST + Linked List       O(log n)
List alphabetically     BST in-order            O(n)
Update contact          BST + Linked List       O(log n)


FILE STRUCTURE
------------------------------------------------------------
Contact.h           - Contact struct (name, phone, email, address)
LinkedList.h        - Doubly Linked List class declaration
LinkedList.cpp      - Doubly Linked List implementation
BST.h               - Binary Search Tree class declaration
BST.cpp             - Binary Search Tree implementation
ContactBook.h       - ContactBook class declaration
ContactBook.cpp     - ContactBook logic combining both structures
main.cpp            - Main menu and user interaction


HOW TO COMPILE AND RUN
------------------------------------------------------------

Requirements:
  - g++ compiler with C++17 support
  - Works on Windows and Linux

Compile:
  g++ main.cpp LinkedList.cpp BST.cpp ContactBook.cpp -o contacts

Run (Linux):
  ./contacts

Run (Windows - MinGW):
  contacts.exe


SAMPLE MENU
------------------------------------------------------------
===== Contact Management System =====
1. Add Contact
2. Search by Name
3. Search by Phone
4. Update Contact
5. Delete Contact
6. List All Contacts (Alphabetical)
0. Exit
======================================
Enter your choice:



============================================================
