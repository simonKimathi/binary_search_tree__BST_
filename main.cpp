#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

struct node *insert(struct node *node, int key);
struct node* search(struct node* root, int key);
string printCurrentLevel(node* root, int level);
string BreadthSearch(node* root);
int height(node* node);
node* newNode(int data);
unsigned int getLeafCount(struct node* node);
struct node* deleteNode(struct node* root, int key);
struct node* minValueNode(struct node* node);
string printInorder(struct node* node);
void maxValue(struct node* node);
void findlargestAndsecondLargest(node *root);
void secondLargest(node *root, int &c);
struct node {
    int key;
    struct node *left, *right;
};
// Create a node
struct node *newNode(int item) {
    struct node *temp = (struct node *)malloc(500);
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}
static bool keyFound;
static struct node*  nodeWithLargestKey;
static struct node*  nodeWithSecondLargestKey;
int main() {
    struct node* tree = NULL;
    string text;
    ifstream MyReadFile("../input-4-2.txt");

    if (MyReadFile.is_open()) {
        while (getline(MyReadFile, text)) {
            // Read the text from the file

            stringstream ssin(text);
            int i = 0, arr[100];
            while (ssin.good() && i < 100) {
                string value;
                ssin >> value;
//                insert into the tree
                tree = insert(tree,stoi(value));
//                insert into an array
                arr[i] = stoi(value);
                ++i;
            }
        }
        //breadth search the tree
        string output;
        output=BreadthSearch(tree);

        //write output to file
        // Create and open a text file
        ofstream MyFile("../output-4-2-1.txt");

        // Write to the file
        MyFile << output;

        //close file
        MyFile.close();
        int treeCount=height(tree);
        int leafCount=getLeafCount(tree);
        output="The height of the tree is " + to_string(treeCount) +". \n";
        output += "The number of leaf nodes " + to_string(leafCount);
        //write output to file
        // Create and open a text file
        ofstream MyFile1("../output-4-2-2.txt");

        // Write to the file
        MyFile1 << output;

        //close the file
        MyFile1.close();

        //search a value
        struct node* results=search(tree,324);
        if(keyFound){
            if(results->right->key != NULL){
                output="The right Key is "+ to_string(results->right->key);
                output += "\n";
            }
            if(results->left->key != NULL){
                output="The right Key is " +to_string(results->left->key);
                output += "\n";
            }

        }
        //delete node
        struct node* resultsAfterDelete = deleteNode(tree,324);

        //Write In order to file
        output = printInorder(resultsAfterDelete);
        // Create and open a text file
        ofstream MyFile2("../output-4-2-3.txt");

        // Write to the file
        MyFile2 << output;

        //close the file
        MyFile2.close();

        // find node with the largest and second-largest value
        findlargestAndsecondLargest(tree);
        output="The largest value is on node of key"+ to_string(nodeWithLargestKey->key);
        output += "\n";
        output +="The Second-largest value is on node of key"+ to_string(nodeWithSecondLargestKey->key);

        // Create and open a text file
        ofstream MyFile3("../output-4-2-3.txt");

        // Write to the file
        MyFile3 << output;

        //close the file
        MyFile3.close();

    }
    //close file
    MyReadFile.close();
    return 0;
}
// Insert a node
struct node *insert(struct node *node, int key) {
    if (node == NULL) return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else
        node->right = insert(node->right, key);

    return node;
}
// C function to search a given key in a given BST
struct node* search(struct node* root, int key)
{
    if (root == NULL ) {
        keyFound = false;
        return nullptr;
    }
    if (root->key == key){
        keyFound= true;
        return root;
    }

    if (root->key < key)
        return search(root->right, key);

    return search(root->left, key);
}

// Function to print level order traversal a tree
string BreadthSearch(node* root)
{
    string output;
    int h = height(root);
    int i;
    for (i = 1; i <= h; i++) {
        output += printCurrentLevel(root, i);
    }
    return output;
}

// Print nodes at a current level
string printCurrentLevel(node* root, int level)
{
    string output="";
    if (root == NULL)
        return output;
    if (level == 1) {
        output += to_string(root->key) + " ";
    }
    else if (level > 1) {
        output += printCurrentLevel(root->left, level - 1);
        output += printCurrentLevel(root->right, level - 1);
    }
    return output;
}

//Compute the "height" of a tree
int height(node* node)
{
    if (node == NULL)
        return 0;
    else {
        int lheight = height(node->left);
        int rheight = height(node->right);

        if (lheight > rheight) {
            return (lheight + 1);
        }
        else {
            return (rheight + 1);
        }
    }
}
unsigned int getLeafCount(struct node* node)
{
    if(node == NULL)
        return 0;
    if(node->left == NULL && node->right == NULL)
        return 1;
    else
        return getLeafCount(node->left)+
               getLeafCount(node->right);
}

//delete a node
struct node* deleteNode(struct node* root, int key)
{
    // base case
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);

    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    else {
        // node has no child
        if (root->left==NULL and root->right==NULL)
            return NULL;

            // node with only one child or no child
        else if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }

        struct node* temp = minValueNode(root->right);

        root->key = temp->key;

        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}
struct node* minValueNode(struct node* node)
{
    struct node* current = node;

    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL)
        current = current->left;

    return current;
}
string printInorder(struct node* node)
{
    string output="";
    if (node == NULL)
        return output;

    /* first recur on left child */
    output += printInorder(node->left);

    /* then print the data of node */
    output+=to_string(node->key)+" ";

    /* now recur on right child */
    output += printInorder(node->right);

    return output;
}
// Function to find 2nd largest element
void findlargestAndsecondLargest(node *root)
{
    int c = 0;
    //find largest
    secondLargest(root, c);
    //find second Largest
    maxValue(root);
}

// A function to find 2nd largest element in a given tree.
void secondLargest(node *root, int &c)
{

    if (root == NULL || c >= 2)
        return;


    secondLargest(root->right, c);

    c++;

    // If c becomes k now, then this is the 2nd largest
    if (c == 2)
    {
        nodeWithSecondLargestKey=root;
        return;
    }

    // Recur for left subtree
    secondLargest(root->left, c);
}


void maxValue(struct node* node)
{
    /* loop down to find the rightmost leaf */
    struct node* current = node;
    while (current->right != NULL) {
        current = current->right;
    }
    nodeWithLargestKey= current;
}
