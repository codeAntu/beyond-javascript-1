// by CodeAntu

#include "stdio.h"
#include "stdlib.h"

// Red Black Tree

// Node structure for Red-Black Tree
struct node {
   int data;            // Data of the node
   struct node *left;   // Pointer to the left child
   struct node *right;  // Pointer to the right child
   int color;           // Color of the node: 0 for black, 1 for red
};

typedef struct node node;  // Typedef to simplify the usage of the struct

// Function to create a new node with given data
node *createNode(int data) {
   node *newNode = (node *)malloc(sizeof(node));
   newNode->data = data;
   newNode->left = NULL;
   newNode->right = NULL;
   newNode->color = 1;  // New nodes are always colored red initially
   return newNode;
}

// Function to get the color of a node, treating NULL nodes as black
int getColor(node *root) {
   if (root == NULL)
      return 0;  // Black color for NULL nodes
   return root->color;
}

// Function to perform left rotation on the given root
node *leftRotate(node *root) {
   node *newRoot = root->right;
   node *temp = newRoot->left;

   newRoot->left = root;
   root->right = temp;

   return newRoot;
}

// Function to perform right rotation on the given root
node *rightRotate(node *root) {
   node *newRoot = root->left;
   node *temp = newRoot->right;

   newRoot->right = root;
   root->left = temp;

   return newRoot;
}

// Function to recolor the nodes during the insertion process
void reColor(node *root) {
   if (root == NULL)
      return;

   root->color = 1;  // Set current node to red
   if (root->left != NULL)
      root->left->color = 0;  // Set left child to black
   if (root->right != NULL)
      root->right->color = 0;  // Set right child to black
}

// Function to insert a node with given data into the Red-Black Tree
node *insert(node *root, int data) {
   // Base case: if the tree is empty, create a new node
   if (root == NULL)
      return createNode(data);

   // Recursive insertion
   if (data < root->data)
      root->left = insert(root->left, data);
   else if (data > root->data)
      root->right = insert(root->right, data);
   else
      return root;  // Duplicate data is not allowed

   // Check and balance the tree based on Red-Black Tree properties
   if (getColor(root->left)) {
      if (getColor(root->left->left)) {
         if (getColor(root->right)) {
            // Case 1: Recolor nodes when both left and right children are red
            reColor(root);
         } else {
            // Case 2: Right rotation when the left-left child is red
            root = rightRotate(root);
            root->color = 0;         // Set root to black
            root->right->color = 1;  // Set right child to red
         }
      } else if (getColor(root->left->right)) {
         if (getColor(root->right)) {
            // Case 3: Recolor nodes when left-right and right children are red
            reColor(root);
         } else {
            // Case 4: Left and right rotation when left-right child is red
            root->left = leftRotate(root->left);
            root = rightRotate(root);
            root->color = 0;         // Set root to black
            root->right->color = 1;  // Set right child to red
         }
      }
   }

   if (getColor(root->right)) {
      if (getColor(root->right->left)) {
         if (getColor(root->left)) {
            // Case 5: Recolor nodes when right-left and left children are red
            reColor(root);
         } else {
            // Case 6: Right and left rotation when right-left child is red
            root->right = rightRotate(root->right);
            root = leftRotate(root);
            root->color = 0;        // Set root to black
            root->left->color = 1;  // Set left child to red
         }
      } else if (getColor(root->right->right)) {
         if (getColor(root->left)) {
            // Case 7: Recolor nodes when right-right and left children are red
            reColor(root);
         } else {
            // Case 8: Left rotation when right-right child is red
            root = leftRotate(root);
            root->color = 0;        // Set root to black
            root->left->color = 1;  // Set left child to red
         }
      }
   }

   return root;
}

// Function to display the nodes of the tree in pre-order
void display(node *root) {
   if (root == NULL)
      return;
   printf("%d ", root->data);
   display(root->left);
   display(root->right);
}

// Main function
int main() {
   node *root = NULL;

   // Insert elements into the Red-Black Tree
   root = insert(root, 7);
   root = insert(root, 6);
   root = insert(root, 5);
   root = insert(root, 4);
   root = insert(root, 3);

   // Display the elements of the Red-Black Tree in pre-order
   printf("Pre-order Traversal: ");
   display(root);

   return 0;
}
