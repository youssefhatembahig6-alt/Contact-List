Contact Management System

PROJECT DESCRIPTION
------------------------------------------------------------
A console-based Contact Management System implemented in C++
using an AVL Tree as the sole data structure. The system allows
users to add, search, update, delete, and list contacts efficiently.

Built as a group project for CSE333 - Data Structures and
Algorithms, Spring 2026.


DATA STRUCTURE USED
------------------------------------------------------------

AVL Tree
   - Used as the only storage structure for all contacts.
   - AVL Tree is a self-balancing Binary Search Tree.
   - After each insertion or deletion, the tree maintains balance
     using rotations (LL, RR, LR, RL).
   - Supports name-based search in O(log n) worst-case time.
   - In-order traversal automatically displays contacts in
     alphabetical order.
   - Improves over a normal BST because it avoids becoming skewed,
     guaranteeing O(log n) in the worst case.
   - Reflects the Trees chapter covered in the course.


FEATURES
------------------------------------------------------------
1. Add a new contact (name, phone number, email, address)
2. Search contact by name                         - O(log n)
3. Update an existing contact's information       - O(log n)
4. Delete a contact                               - O(log n)
5. Display all contacts in alphabetical order     - O(n)


TIME COMPLEXITY SUMMARY
------------------------------------------------------------
Operation               Data Structure        Complexity
---------               --------------        ----------
Add contact             AVL Tree              O(log n)
Search by name          AVL Tree              O(log n)
Delete contact          AVL Tree              O(log n)
Update contact          AVL Tree              O(log n)
List alphabetically     AVL in-order          O(n)


NOTES ABOUT COMPLEXITY
------------------------------------------------------------
- All AVL Tree operations (search, insert, delete) are O(log n)
  in the worst case because the tree stays balanced after every
  operation through rotations.
- Listing all contacts uses in-order traversal which visits
  every node once, giving O(n).
- Updating a contact works by removing the old record and
  inserting the updated one. If the name changes, the tree
  re-orders it automatically since ordering is based on name.


FILE STRUCTURE
------------------------------------------------------------
Contact.h           - Contact struct (name, phone, email, address)
AvlTree.h           - AVL Tree class declaration
Avl.cpp             - AVL Tree implementation
main.cpp            - Main menu and user interaction


HOW TO COMPILE AND RUN
------------------------------------------------------------

Requirements:
  - g++ compiler with C++17 support
  - Works on Windows and Linux

Compile:
  g++ main.cpp Avl.cpp -o contacts

Run (Linux):
  ./contacts

Run (Windows - MinGW):
  contacts.exe


SAMPLE MENU
------------------------------------------------------------
===== Contact Management System =====
1. Add Contact
2. Search by Name
3. Update Contact
4. Delete Contact
5. List All Contacts (Alphabetical)
6. Exit
======================================
Enter your choice:


