# Contact Management System

**Course:** CSE333 — Data Structures and Algorithms, Spring 2026

---

## Group Members

| Name | ID |
|------|----|
|Youssef Hatem |2300837|
|Ahmed Ayman   |2300145|
|Yassin Ayman  |2301087|
|Moaz Ali      |2300777|
|Zeyad Saeed   |2300248|

---

## Project Description

A Contact Management System implemented in C++ using an **AVL Tree** as the sole data structure. The system allows users to add, search, update, delete, and list contacts efficiently. Available as a **Qt-based GUI** that mimics a phone contacts app, with full **MySQL database persistence** so contacts are saved between sessions.

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
| 6 | Persist contacts to MySQL database | — |
| 7 | Load contacts from database on startup | — |

### Qt GUI (Phone-Style)

A modern dark-themed desktop GUI built with **Qt Widgets** that mimics a phone contacts app:

- Contacts list always displayed alphabetically with **letter section headers (A, B, C…)**
- **Colored avatar circles** generated from the contact's initials
- **Live search bar** — filters contacts as you type
- **`+` button** to add a new contact via a clean dialog
- **Click any contact** to view full details with Edit and Delete options
- Phone number **validation** on add and edit
- Duplicate phone number **prevention**
- All changes **automatically saved to MySQL** and reloaded on next launch

---

## File Structure

```
Contact-List/
├── .gitignore
├── README.md
└── project_root/
    ├── main.cpp                  — Qt entry point
    ├── mainwindow.h              — Qt window class declaration
    ├── mainwindow.cpp            — Qt GUI logic + DB integration
    ├── mainwindow.ui             — Qt Designer layout (XML)
    ├── ContactList.pro           — Qt project file
    └── src/
        ├── Contact.h             — Contact struct (name, phone, email, address)
        ├── AvlTree.h             — AVL Tree class declaration
        ├── Avl.cpp               — AVL Tree implementation
        ├── Database.h            — MySQL Database class declaration
        ├── Database.cpp          — MySQL Database implementation
        ├── contacts.sql          — MySQL schema (run once before first launch)
        └── db_config.h.example   — Database credentials template
```

> **Note:** `db_config.h` is not included in the repo (contains credentials). Copy `db_config.h.example` to `db_config.h` and fill in your own credentials.

---

## Setup & How to Run

### Step 1 — Set your database credentials

Copy the example config file and fill in your MySQL credentials:

**🐧 Linux:**
```bash
cp project_root/src/db_config.h.example project_root/src/db_config.h
```

**🪟 Windows:**
```cmd
copy project_root\src\db_config.h.example project_root\src\db_config.h
```

Then open `db_config.h` and edit it:
```cpp
#ifndef DB_CONFIG_H
#define DB_CONFIG_H

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS "your_password_here"   // ← put your MySQL password here
#define DB_NAME "contact_db"
#define DB_PORT 3306

#endif
```

---

### Step 2 — Install Requirements

#### 🐧 Linux (Fedora/RHEL)
```bash
sudo dnf install mysql-server mysql-devel -y
```

#### 🐧 Linux (Ubuntu/Debian)
```bash
sudo apt install mysql-server libmysqlclient-dev -y
```

#### 🪟 Windows
1. Download and install **MySQL Community Server** from https://dev.mysql.com/downloads/mysql/
2. Download and install **MySQL Connector/C** from https://dev.mysql.com/downloads/connector/c/
3. Make sure MySQL is added to your system PATH during installation

---

### Step 3 — Start MySQL

#### 🐧 Linux
```bash
sudo systemctl start mysqld
sudo systemctl enable mysqld   # optional: auto-start on boot
```

#### 🪟 Windows
MySQL starts automatically after installation. If not, open **Services** from the Start menu and start **MySQL80**.

Or from Command Prompt (as Administrator):
```cmd
net start MySQL80
```

---

### Step 4 — Create the Database (run once)

#### 🐧 Linux
```bash
cd ~/Contact-List/project_root/src
mysql -u root -p < contacts.sql
```

#### 🪟 Windows (Command Prompt)
```cmd
cd C:\path\to\Contact-List\project_root\src
mysql -u root -p < contacts.sql
```

Or open **MySQL Workbench** → File → Open SQL Script → select `contacts.sql` → click ⚡ Execute.

---

### Step 5 — Build and Run

#### 🐧 Linux
```bash
cd ~/Contact-List/project_root/build
qmake ../ContactList.pro
make
./ContactList
```

#### 🪟 Windows (Qt Creator — recommended)
1. Open **Qt Creator**
2. File → Open File or Project → select `ContactList.pro`
3. In `ContactList.pro`, make sure these lines exist:
```
INCLUDEPATH += C:/Program Files/MySQL/MySQL Connector C 6.1/include
LIBS += -LC:/Program Files/MySQL/MySQL Connector C 6.1/lib -lmysqlclient
```
4. Press `Ctrl+B` to build, `Ctrl+R` to run

#### 🪟 Windows (Command Prompt with MinGW)
```cmd
cd C:\path\to\Contact-List\project_root\build
qmake ../ContactList.pro
mingw32-make
ContactList.exe
```

---

## Time Complexity Summary

| Operation | Data Structure | Complexity |
|-----------|---------------|------------|
| Add contact | AVL Tree + MySQL INSERT | O(log n) |
| Search by name | AVL Tree | O(log n) |
| Delete contact | AVL Tree + MySQL DELETE | O(log n) |
| Update contact | AVL Tree + MySQL UPDATE | O(log n) |
| List alphabetically | AVL in-order traversal | O(n) |
| Load on startup | MySQL SELECT | O(n) |

---

## AI Usage Declaration

AI tools were used to assist in developing the Qt-based GUI and MySQL database integration. This includes help with designing the interface layout, widget styling, GUI logic, and database connectivity. All core data structure logic (AVL Tree operations) was implemented independently by the team.

---