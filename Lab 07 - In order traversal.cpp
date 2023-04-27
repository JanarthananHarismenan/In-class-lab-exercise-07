#include <iostream>
using namespace std;

struct node 
{
  int key;
  struct node *left, *right;
};

// Function to create a new node
struct node *createNode(int key)
{
  struct node *newNode = new node;
  newNode->key = key;
  newNode->left = newNode->right = NULL;
  return newNode;
}

// Inorder traversal
void traverseInOrder(struct node *root) 
{
  if (!root) return;
  
  traverseInOrder(root->left);
  cout << root->key << " ";
  traverseInOrder(root->right);
}

// Insert a node
struct node *insertNode(struct node *root, int key) 
{
  if (!root) return createNode(key);

  if (key < root->key) 
  {
    if (!root->left) root->left = createNode(key);
    else insertNode(root->left, key);
  }
  else if (key > root->key) 
  {
    if (!root->right) root->right = createNode(key);
    else insertNode(root->right, key);
  }

  return root;
}

// Function to find the node with minimum key value in a subtree rooted at given node
struct node *minValueNode(struct node *node) 
{
  struct node *current = node;

  while (current && current->left != NULL)
    current = current->left;

  return current;
}

// Deleting a node
struct node *deleteNode(struct node *root, int key) 
{
  if (root == NULL)
    return root;

  if (key == root->key) 
  {
    if (root->left == NULL && root->right == NULL) 
    {
      // Node with no children
      delete root;
      return NULL;
    } 
    else if (root->left == NULL || root->right == NULL) 
    {
      // Node with one child
      struct node *child = root->left ? root->left : root->right;
      delete root;
      return child;
    } 
    else 
    {
      // Node with two children
      struct node *minRight = minValueNode(root->right);
      root->key = minRight->key;
      root->right = deleteNode(root->right, minRight->key);
      return root;
    }
  } 
  else if (key < root->key)
    root->left = deleteNode(root->left, key);
  else
    root->right = deleteNode(root->right, key);

  return root;
}

// Driver code
int main() 
{
  struct node *root = NULL;

  int operation;
  int operand;
  cin >> operation;

  while (operation != -1) 
  {
    switch(operation) 
    {
      case 1: // insert
        cin >> operand;
        root = insertNode(root, operand);
        cin >> operation;
        break;
      case 2: // delete
        cin >> operand;
        root = deleteNode(root, operand);
        cin >> operation;
        break;
      default:
        cout << "Invalid Operator!\n";
        return 0;
    }
  }
  
  traverseInOrder(root);
}
