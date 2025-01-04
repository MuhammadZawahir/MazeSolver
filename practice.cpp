#include <iostream>
using namespace std;

// Define the structure for a tree node
struct Node
{
    int data;    // Data stored in the node
    Node *left;  // Pointer to the left child
    Node *right; // Pointer to the right child
    int height;  // Height of the node for balancing

    // Constructor to create a new node
    Node(int value)
    {
        data = value;
        left = right = nullptr;
        height = 1; // Height of new node is 1
    }
};

// Function to get the height of a node
int height(Node *root)
{
    if (root == nullptr)
        return 0;
    return root->height;
}

// Function to calculate the balance factor
int balanceFactor(Node *root)
{
    if (root == nullptr)
        return 0;
    return height(root->left) - height(root->right);
}

// Right rotation (used for balancing)
Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x; // New root
}

// Left rotation (used for balancing)
Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y; // New root
}

// Function to insert a node and balance the tree
Node *insert(Node *root, int value)
{
    // Step 1: Perform the normal BST insertion
    if (root == nullptr)
        return new Node(value);

    if (value < root->data)
        root->left = insert(root->left, value);
    else if (value > root->data)
        root->right = insert(root->right, value);
    else
        return root; // Duplicate values are not allowed

    // Step 2: Update the height of this ancestor node
    root->height = max(height(root->left), height(root->right)) + 1;

    // Step 3: Get the balance factor of this node
    int balance = balanceFactor(root);

    // Step 4: Balance the node if necessary
    // Left heavy (Right Rotation)
    if (balance > 1 && value < root->left->data)
        return rightRotate(root);

    // Right heavy (Left Rotation)
    if (balance < -1 && value > root->right->data)
        return leftRotate(root);

    // Left-right heavy (Left Rotation, then Right Rotation)
    if (balance > 1 && value > root->left->data)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right-left heavy (Right Rotation, then Left Rotation)
    if (balance < -1 && value < root->right->data)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    // Return the (unchanged) node pointer
    return root;
}

// Function to perform an in-order traversal of the tree
void inorderTraversal(Node *root)
{
    if (root != nullptr)
    {
        inorderTraversal(root->left);
        cout << root->data << " ";
        inorderTraversal(root->right);
    }
}

// Main function to test the AVL tree
int main()
{
    Node *root = nullptr;

    // Inserting values into the AVL tree
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    cout << "In-order traversal of the AVL tree: ";
    inorderTraversal(root); // Output will be sorted order
    cout << endl;

    return 0;
}
