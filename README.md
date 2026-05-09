# Contact Management System

## Project Description

A Contact Management System implemented in C++ using an **AVL Tree** as the sole data structure. The system allows users to add, search, update, delete, and list contacts efficiently. Available in both a **console interface** and a **Qt-based GUI** that mimics a phone contacts app.

Built as a group project for **CSE333 - Data Structures and Algorithms, Spring 2026.**

---

## Data Structure Used

### AVL Tree
- Used as the only storage structure for all contacts.
- A self-balancing Binary Search Tree (BST).
- After each insertion or deletion, the tree maintains balance using rotations (LL, RR, LR, RL).
- Supports name-based search in **O(log n)** worst-case time.
- In-order traversal automatically displays contacts in alphabetical order.
- Improves over a normal BST by avoiding skewed trees, guaranteeing O(log n) in the worst case.
- Reflects the **Trees** chapter covered in the course.

---

## Features

| # | Feature | Complexity |
|---|---------|------------|
| 1 | Add a new contact (name, phone, email, address) | O(log n) |
| 2 | Search contact by name | O(log n) |
| 3 | Update an existing contact | O(log n) |
| 4 | Delete a contact | O(log n) |
| 5 | Display all contacts in alphabetical order | O(n) |

---


### Qt GUI (Phone-Style)
A modern dark-themed desktop GUI built with **Qt Widgets** that mimics a phone contacts app.

- Contacts list always displayed in alphabetical order with **letter section headers (A, B, C...)**
- **Colored avatar circles** generated from the contact's name
- **Live search bar** — filters contacts as you type
- **`+` button** to add a new contact via a clean dialog
- **Click any contact** to view full details with Edit and Delete options
- Phone number **validation** on add and edit
- Duplicate phone number **prevention**

---

## Time Complexity Summary

| Operation | Data Structure | Complexity |
|-----------|---------------|------------|
| Add contact | AVL Tree | O(log n) |
| Search by name | AVL Tree | O(log n) |
| Delete contact | AVL Tree | O(log n) |
| Update contact | AVL Tree (remove + insert) | O(log n) |
| List alphabetically | AVL in-order traversal | O(n) |

> **Note:** Updating works by removing the old record and inserting the updated one. If the name changes, the tree re-orders it automatically since ordering is name-based.

---

## File Structure

```
project_root/
├── main.cpp              — Qt entry point
├── mainwindow.h          — Qt window class declaration
├── mainwindow.cpp        — Qt GUI logic
├── mainwindow.ui         — Qt Designer layout (XML)
├── ContactList.pro       — Qt project file
└── src/
    ├── Contact.h         — Contact struct (name, phone, email, address)
    ├── AvlTree.h         — AVL Tree class declaration
    ├── Avl.cpp           — AVL Tree implementation
    └── main.cpp          — Console menu and user interaction
```

---

## How to Compile and Run

### Console Version

**Requirements:** g++ with C++17 support

```bash
# Compile
g++ src/main.cpp src/Avl.cpp -o contacts

# Run (Linux/Mac)
./contacts

# Run (Windows)
contacts.exe
```

### Qt GUI Version

**Requirements:** Qt 6 (or Qt 5.15+) with Qt Widgets, Qt Creator

```bash
# Open in Qt Creator
File → Open File or Project → select ContactList.pro

# Configure with Desktop kit, then:
Ctrl+B   # Build
Ctrl+R   # Run
```

---

## Notes

- All AVL Tree operations are **O(log n)** in the worst case because the tree stays balanced after every operation through rotations.
- Listing all contacts uses in-order traversal which visits every node once — **O(n)**.
- The GUI uses a **function pointer callback** pattern to traverse the AVL tree and populate the UI without relying on STL containers, keeping the data structure implementation pure.
