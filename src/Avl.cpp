#include "AvlTree.h"

//Default constructor
AvlTree::AvlTree():root(nullptr) {}

//Destructor
AvlTree::~AvlTree() {
    deleteAll(root);
}

void AvlTree::deleteAll(Node *&node){
    if(node->right == nullptr && node->right == nullptr )
      delete node;
    deleteAll(node->left);
    deleteAll(node->right);

}








//Display  assending
void AvlTree::display(){ 
    inorder(root);
}

void AvlTree::inorder(Node* node){
    if(node == nullptr)
      return;
    inorder(node->left);
    cout<< node->data.name<< " ";
    inorder(node->right);
}








// Rotate Functions

//Left Rotation
AvlTree::Node* AvlTree::leftRotate(Node * x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));
    return y;
 
} 

//Right Rotation
AvlTree::Node* AvlTree::rightRotate(Node * y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));
    return x;

} 




 





//Supporter function to get balance Factor
int AvlTree::height(AvlTree::Node* n) {
    return (n == nullptr) ? 0 : n->height;
}

int AvlTree::getBalance(AvlTree::Node* n) {
    if (n == nullptr) return 0;
    return height(n->left) - height(n->right);
}












// Insert function
void AvlTree::AddContact(const Contact& item)
{
     root = insert(root, item);
}

AvlTree::Node* AvlTree::insert(AvlTree::Node *s, const Contact &c) {
    
    // 1. Normal BST insert
    if (s == nullptr)
        return new Node(c);

    if (c.name < s->data.name)
        s->left = insert(s->left, c);

    else if (c.name > s->data.name)
        s->right = insert(s->right, c);

    else {
        // same name → compare phone
        if (c.phone < s->data.phone)
            s->left = insert(s->left, c);
        else if (c.phone > s->data.phone)
            s->right = insert(s->right, c);
        else
            return s; // duplicate
    }

    // 2. Update height
    s->height = 1 + max(height(s->left), height(s->right));

    // 3. Get balance factor
    int balance = getBalance(s);
  
    // 4. AVL Rebalancing cases
    
    // Left Left Rotation
    if (balance > 1 && c.name < s->left->data.name)
        return rightRotate(s);

    // Right Right Rotation
    if (balance < -1 && c.name > s->right->data.name)
        return leftRotate(s);

    // Left Right Rotation
    if (balance > 1 && c.name > s->left->data.name) {
        s->left = leftRotate(s->left);
        return rightRotate(s);
    }

    // Right Left Rotation
    if (balance < -1 && c.name < s->right->data.name) {
        s->right = rightRotate(s->right);
        return leftRotate(s);
    }

    return s;

}


//Search about spacific contact
Contact  AvlTree::SearchReq(string name){
    return SearchReqAux(root,name);
}

Contact AvlTree::SearchReqAux(Node *&node, string name){

    if(node==nullptr) return Contact();
    else if(name < node->data.name) SearchReqAux(node->left, name);
    else if(name > node->data.name) SearchReqAux(node->right, name);
    else   return node->data;
    
}




// Delete one Element and rebalnce avl
void AvlTree::Removecontact(string name)
{
   root = remove(root, name);
}

AvlTree::Node* AvlTree::remove(AvlTree::Node *s, string name){






}














