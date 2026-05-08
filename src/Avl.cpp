#include "AvlTree.h"

// ── Public ────────────────────────────────────────────────


// start with an empty tree
AvlTree::AvlTree():root(nullptr) {}

// clean up everything when the program ends
AvlTree::~AvlTree() {
    deleteAll(root);
}

// just a wrapper to kick off the recursive insert
bool AvlTree::AddContact(const Contact& item) {
    if (searchByPhone(root, item.phone)) {
        cout << "A contact with phone number \"" << item.phone << "\" already exists.\n";
        return false;
    }
    root = insert(root, item);
    return true;
}

// before deleting, make sure the contact actually exists
void AvlTree::RemoveContact(const string& name) {
    Contact found = SearchReq(name);
    if (found.name.empty()) {
        cout << "Contact \"" << name << "\" not found.\n";
        return;
    }
    root = remove(root, name);
    cout << "Contact \"" << name << "\" removed successfully.\n";
}


// show current info, let the user change whatever they want,
// then remove the old record and insert the updated one
void AvlTree::UpdateContact(const string& name) {
    Contact existing = SearchReq(name);
    if (existing.name.empty()) {
        cout << "Contact \"" << name << "\" not found.\n";
        return;
    }
    cout << "\nCurrent details for \"" << name << "\":\n";
    cout << "  1. Name   : " << existing.name    << "\n";
    cout << "  2. Phone  : " << existing.phone   << "\n";
    cout << "  3. Email  : " << existing.email   << "\n";
    cout << "  4. Address: " << existing.address << "\n";
    cout << "\nEnter new values (press Enter to keep current):\n";
    string input;
    cout << "New Name    [" << existing.name    << "]: "; getline(cin, input);
    if (!input.empty()) existing.name    = input;
    cout << "New Phone   [" << existing.phone   << "]: "; getline(cin, input);
    if (!input.empty()) existing.phone   = input;
    cout << "New Email   [" << existing.email   << "]: "; getline(cin, input);
    if (!input.empty()) existing.email   = input;
    cout << "New Address [" << existing.address << "]: "; getline(cin, input);
    if (!input.empty()) existing.address = input;
    // we remove first because if the name changed, the tree order changes too
    root = remove(root, name);
    root = insert(root, existing);
    cout << "Contact updated successfully.\n";
}


// just a wrapper to kick off the recursive search
Contact AvlTree::SearchReq(const string& name) {
    return SearchReqAux(root, name);
}


// just a wrapper to kick off the inorder traversal
void AvlTree::display() {
    inorder(root);
}
// ── Private ───────────────────────────────────────────────


// go left, then right, then delete — so we never lose a child before freeing it
void AvlTree::deleteAll(Node*& node) {
    if (node == nullptr) return;
    deleteAll(node->left);
    deleteAll(node->right);
    delete node;
    node = nullptr;
}


// inorder traversal gives us alphabetical order for free (that's the point of BST)
void AvlTree::inorder(Node* node) {
    if (node == nullptr) return;
    inorder(node->left);
    cout << "Name   : " << node->data.name    << "\n";
    cout << "Phone  : " << node->data.phone   << "\n";
    cout << "Email  : " << node->data.email   << "\n";
    cout << "Address: " << node->data.address << "\n";
    cout << "----------------------------\n";
    inorder(node->right);
}


// x is out of balance to the right, so we pull y up to fix it
AvlTree::Node* AvlTree::leftRotate(Node* x) {
    Node* y  = x->right;
    Node* T2 = y->left;   // T2 will be re-attached to x after the rotation

    y->left  = x;
    x->right = T2;

    // y is now higher up so we update x first, then y
    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));
    return y;  // y is the new root of this subtree
}


// mirror of leftRotate — y is out of balance to the left
AvlTree::Node* AvlTree::rightRotate(Node* y) {
    Node* x  = y->left;
    Node* T2 = x->right;  // T2 will be re-attached to y after the rotation

    x->right = y;
    y->left  = T2;

    // same idea — update the lower node first
    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));
    return x;  // x is the new root of this subtree
}


// null nodes have height 0, everything else reads from the stored value
int AvlTree::height(Node* n) {
    return (n == nullptr) ? 0 : n->height;
}


// positive means left-heavy, negative means right-heavy, 0 is perfectly balanced
int AvlTree::getBalance(Node* n) {
    if (n == nullptr) return 0;
    return height(n->left) - height(n->right);
}


// standard BST insert + AVL rebalancing on the way back up
AvlTree::Node* AvlTree::insert(Node* s, const Contact& c) {
    
    // base case — found the empty spot, put the new node here
    if (s == nullptr)
        return new Node(c);
    // go left or right based on name
    if (c.name < s->data.name)
        s->left = insert(s->left, c);
    else if (c.name > s->data.name)
        s->right = insert(s->right, c);
    else {
        // same name? use phone number as a tiebreaker
        if (c.phone < s->data.phone)
            s->left = insert(s->left, c);
        else if (c.phone > s->data.phone)
            s->right = insert(s->right, c);
        else
            return s; // exact duplicate, don't insert
    }
    // update this node's height now that a new node was added below it
    s->height = 1 + max(height(s->left), height(s->right));
    int balance = getBalance(s);
    // check all 4 imbalance cases and fix them with rotations
    if (balance > 1  && c.name < s->left->data.name)  return rightRotate(s);               // Left Left
    if (balance < -1 && c.name > s->right->data.name) return leftRotate(s);                // Right Right
    if (balance > 1  && c.name > s->left->data.name)  { s->left  = leftRotate(s->left);  return rightRotate(s); }  // Left Right
    if (balance < -1 && c.name < s->right->data.name) { s->right = rightRotate(s->right); return leftRotate(s); } // Right Left
    return s; // already balanced, nothing to do
}


// standard BST delete + AVL rebalancing on the way back up
AvlTree::Node* AvlTree::remove(Node* s, const string& name) {
    if (s == nullptr) return s;
    // search for the node to delete
    if (name < s->data.name)
        s->left = remove(s->left, name);
    else if (name > s->data.name)
        s->right = remove(s->right, name);
    else {
        // found it — handle the 3 cases

        // case 1: no left child, just return the right
        if (s->left == nullptr) { Node* temp = s->right; delete s; return temp; }
        // case 2: no right child, just return the left
        if (s->right == nullptr) { Node* temp = s->left;  delete s; return temp; }
        // case 3: two children — find the inorder successor (smallest in right subtree)
        // we copy its data here and delete it down there
        Node* successor = s->right;
        while (successor->left != nullptr)
            successor = successor->left;
        s->data  = successor->data;
        s->right = remove(s->right, successor->data.name);
    }
    // update height after the deletion
    s->height = 1 + max(height(s->left), height(s->right));
    int balance = getBalance(s);
    // same 4 rotation cases as insert, but using balance of children instead of key comparison
    if (balance > 1  && getBalance(s->left)  >= 0) return rightRotate(s);                                          // Left Left
    if (balance > 1  && getBalance(s->left)  <  0) { s->left  = leftRotate(s->left);   return rightRotate(s); }   // Left Right
    if (balance < -1 && getBalance(s->right) <= 0) return leftRotate(s);                                           // Right Right
    if (balance < -1 && getBalance(s->right) >  0) { s->right = rightRotate(s->right); return leftRotate(s);  }   // Right Left
    return s;
}


// traverse every node looking for a matching phone number
bool AvlTree::searchByPhone(Node* node, const string& phone) {
    if (node == nullptr) return false;
    if (node->data.phone == phone) return true;
    return searchByPhone(node->left, phone) || searchByPhone(node->right, phone);
}

// standard BST search — go left if smaller, right if bigger, return when found
Contact AvlTree::SearchReqAux(Node* node, const string& name) {
    if (node == nullptr)        return Contact();  // not found, return empty contact
    if (name < node->data.name) return SearchReqAux(node->left,  name);
    if (name > node->data.name) return SearchReqAux(node->right, name);
    return node->data;  // found it
}