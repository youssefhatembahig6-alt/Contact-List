# Contact Management System

**Course:** CSE333 — Data Structures and Algorithms, Spring 2026

---

## Group Members

| Name | ID |
|------|----|
|Youssef Hatem |2300837|
|Ahmed Ayman   |2300145|
|Yassin Ayman  |2301087|    |
|Moaz Ali      |2300777|
|Zeyad Saeed   |2300248|

---

## Project Description

A Contact Management System implemented in C++ using an **AVL Tree** as the sole data structure. The system allows users to add, search, update, delete, and list contacts efficiently. Available in both a **console interface** and a **Qt-based GUI** that mimics a phone contacts app.

---

## Data Structure Used

### AVL Tree

The AVL Tree was chosen as the only storage structure for all contacts for the following reasons:

- It is a **self-balancing Binary Search Tree (BST)** that guarantees **O(log n)** performance in the worst case for insertion, deletion, and search — unlike a regular BST which can degrade to O(n) on skewed input.
- After each insertion or deletion, the tree maintains balance automatically using **rotations (LL, RR, LR, RL)**.
- **In-order traversal** naturally produces contacts in alphabetical order, making sorted display O(n) with no extra sorting step.
- Name-based ordering makes it a natural fit for a contacts app where lookup by name is the primary operation.
- The structure directly reflects the **Trees** chapter covered in CSE333.

---

## Features

| # | Feature | Complexity |
|---|---------|------------|
| 1 | Add a new contact (name, phone, email, address) | O(log n) |
| 2 | Search contact by name | O(log n) |
| 3 | Update an existing contact | O(log n) |
| 4 | Delete a contact | O(log n) |
| 5 | Display all contacts in alphabetical order | O(n) |

### Qt GUI (Phone-Style)

A modern dark-themed desktop GUI built with **Qt Widgets** that mimics a phone contacts app:

- Contacts list always displayed alphabetically with **letter section headers (A, B, C…)**
- **Colored avatar circles** generated from the contact's initials
- **Live search bar** — filters contacts as you type
- **`+` button** to add a new contact via a clean dialog
- **Click any contact** to view full details with Edit and Delete options
- Phone number **validation** on add and edit
- Duplicate phone number **prevention**

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

# Configure with a Desktop kit, then:
Ctrl+B   # Build
Ctrl+R   # Run
```

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

## AI Usage Declaration

AI tools were used to assist in developing the Qt-based GUI. This includes help with designing the interface layout, widget styling, and GUI logic implementation. All core data structure logic (AVL Tree operations) was implemented independently by the team.

---
