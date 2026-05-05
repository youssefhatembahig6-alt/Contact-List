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

1. Doubly Linked List
   - Used as the primary storage structure for all contacts.
   - Allows efficient insertion at the end in O(1)
   - Allows efficient deletion once the node pointer is known in O(1)
   - Allows full traversal for phone-based search in O(n)
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


------------------------------------------------------------



What was modified or rejected:
  - AI suggested using std::unordered_map for O(1) phone lookup.
    We rejected this because hash maps were not covered in our syllabus
    and we could not fully justify the internal implementation.
  - AI also suggested using std::map instead of a custom BST.
    We replaced it with a hand-written BST to match our course
    material (Ch06) and ensure we could explain every part.



What the group implemented themselves:
  - All BST operations (insert, search, delete, in-order traversal)
  - All Linked List operations (insert, delete, traverse)
  - The ContactBook integration layer connecting both structures
  - The main menu and input handling in main.cpp
  - The design decision to use phone number as the primary key


