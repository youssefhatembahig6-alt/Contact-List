Contact Management System

PROJECT DESCRIPTION
------------------------------------------------------------
A console-based Contact Management System implemented in C++
using core data structures. The system allows users to add,
search, update, delete, and list contacts efficiently.

The project uses a Singly Linked List as the main storage
structure and an AVL Tree to index contacts by name for faster
and balanced searching.

Built as a group project for CSE333 - Data Structures and
Algorithms, Spring 2026.


DATA STRUCTURES USED
------------------------------------------------------------

1. Singly Linked List
   - Used as the primary storage structure for all contacts.
   - Allows insertion at the end by traversing to the last node in O(n).
   - Allows deletion using two pointers (prev + current) in O(n).
   - Since all phone-based operations require traversal anyway,
     a singly linked list is sufficient and simple to implement.
   - Reflects the List chapter covered in the course.

2. AVL Tree
   - Used to index all contacts by name for fast retrieval and sorted output.
   - AVL Tree is a self-balancing Binary Search Tree.
   - After each insertion or deletion, the tree maintains balance using rotations.
   - Supports name-based search in O(log n) worst-case time.
   - In-order traversal automatically displays contacts in alphabetical order.
   - Improves over a normal BST because it avoids becoming skewed.
   - Reflects the Trees chapter covered in the course.


FEATURES
------------------------------------------------------------
1. Add a new contact (name, phone number, email, address)
2. Search contact by name using AVL Tree          - O(log n)
3. Search contact by phone using Linked List      - O(n)
4. Update an existing contact's information
5. Delete a contact from both the Linked List and the AVL Tree
6. Display all contacts in alphabetical order using AVL in-order traversal


TIME COMPLEXITY SUMMARY
------------------------------------------------------------
Operation               Data Structure              Complexity
---------               --------------              ----------
Add contact             Linked List + AVL Tree       O(log n)
Search by name          AVL Tree                     O(log n)
Search by phone         Linked List                  O(n)
Delete contact          AVL Tree + Linked List       O(log n) + O(n)
List alphabetically     AVL in-order traversal       O(n)
Update contact          AVL Tree + Linked List       O(log n) + O(n)


NOTES ABOUT COMPLEXITY
------------------------------------------------------------
- AVL Tree operations such as search, insertion, and deletion are O(log n)
  in the worst case because the tree remains balanced.
- Phone-based searching is O(n) because the phone number is searched
  by traversing the Linked List.
- Updating a contact may require searching in both structures, depending
  on what information is updated.
- If the contact name changes, the old name should be removed from the
  AVL Tree and the updated contact should be inserted again.


FILE STRUCTURE
------------------------------------------------------------
Contact.h           - Contact struct (name, phone, email, address)
LinkedList.h        - Singly Linked List class declaration
LinkedList.cpp      - Singly Linked List implementation
AVLTree.h           - AVL Tree class declaration
AVLTree.cpp         - AVL Tree implementation
ContactBook.h       - ContactBook class declaration
ContactBook.cpp     - ContactBook logic combining both structures
main.cpp            - Main menu and user interaction


HOW TO COMPILE AND RUN
------------------------------------------------------------

Requirements:
  - g++ compiler with C++17 support
  - Works on Windows and Linux

Compile:
  g++ main.cpp LinkedList.cpp AVLTree.cpp ContactBook.cpp -o contacts

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
