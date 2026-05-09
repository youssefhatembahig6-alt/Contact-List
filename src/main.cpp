#include <iostream>
#include <limits>
#include <string>
#include <algorithm>
#include "AvlTree.h"
#include "validation.cpp"
using namespace std;

// ─────────────────────────────────────────────
//  Helper: clear the input buffer safely
// ─────────────────────────────────────────────
void clearInput() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ─────────────────────────────────────────────
//  Menu display
// ─────────────────────────────────────────────
void showMenu() {
    cout << "\n  +==================================+\n";
    cout << "  |       CONTACT MANAGER (AVL)      |\n";
    cout << "  +==================================+\n";
    cout << "  |  1. Add Contact                  |\n";
    cout << "  |  2. Remove Contact               |\n";
    cout << "  |  3. Search Contact               |\n";
    cout << "  |  4. Update Contact               |\n";
    cout << "  |  5. Display All Contacts         |\n";
    cout << "  |  6. Exit                         |\n";
    cout << "  +==================================+\n";
    cout << "  Choice: ";
}

// ─────────────────────────────────────────────
//  Feature handlers
// ─────────────────────────────────────────────

void handleAdd(AvlTree& tree) {
    Contact c;
    cout << "\n  -- Add New Contact --------------------------------\n";

    string n;
    cout << "  Name    : "; getline(cin, n);
    transform(n.begin(), n.end(), n.begin(), ::tolower);
    c.name = n;

    // phone validation loop
    while (true) {
        cout << "  Phone   : "; getline(cin, c.phone);
        if (isValidPhone(c.phone)) break;
        cout << "  Invalid phone. Use digits only, optional leading +.\n";
    }

    cout << "  Email   : "; getline(cin, c.email);
    cout << "  Address : "; getline(cin, c.address);

    if (c.name.empty()) {
        cout << "  Name cannot be empty. Contact not added.\n";
        return;
    }
    if (tree.AddContact(c))
        cout << "  Contact \"" << c.name << "\" added successfully.\n";
}



void handleRemove(AvlTree& tree) {
    string name;
    cout << "\n  -- Remove Contact ---------------------------------\n";
    cout << "  Enter name to remove: ";
    getline(cin, name);
    tree.RemoveContact(name);
}

void handleSearch(AvlTree& tree) {
    string name;
    cout << "\n  -- Search Contact ---------------------------------\n";
    cout << "  Enter name to search: ";
    getline(cin, name);

    Contact result = tree.SearchReq(name);
    if (result.name.empty()) {
        cout << "  Contact \"" << name << "\" not found.\n";
    } else {
        cout << "\n  +-----------------------------------+\n";
        cout << "  | Name   : " << result.name    << "\n";
        cout << "  | Phone  : " << result.phone   << "\n";
        cout << "  | Email  : " << result.email   << "\n";
        cout << "  | Address: " << result.address << "\n";
        cout << "  +-----------------------------------+\n";
        }
}

void handleUpdate(AvlTree& tree) {
    string name;
    cout << "\n  -- Update Contact ---------------------------------\n";
    cout << "  Enter name of contact to update: ";
    getline(cin, name);
    tree.UpdateContact(name);
}

// ─────────────────────────────────────────────
//  Entry point
// ─────────────────────────────────────────────
int main() {
    AvlTree tree; 
    int choice;
    cout << "\n  Welcome to Contact Manager (AVL Tree)\n";

   while (true) {
    showMenu();
    cin >> choice;

    if (cin.fail()) {
        cin.clear();
        clearInput();   // reuse your existing function to flush the bad input
        cout << "  Invalid input. Please enter a number (1-6).\n";
        continue;
    }

    clearInput();   // consume leftover newline (normal case)

    switch (choice) {
        case 1: handleAdd(tree);        break;
        case 2: handleRemove(tree);     break;
        case 3: handleSearch(tree);     break;
        case 4: handleUpdate(tree);     break;
        case 5: tree.display();         break;
        case 6:
            cout << "\n  Goodbye!\n\n";
            return 0;
        default:
            cout << "  Invalid choice. Please enter 1-6.\n";
    }
}
}