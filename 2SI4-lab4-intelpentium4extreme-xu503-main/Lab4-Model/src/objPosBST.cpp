#include "objPosBST.h"

#include <iostream>
using namespace std;

objPosBST::objPosBST()
{
    root = NULL;
    // Constructor (Check Lecture Notes for Implementation, Simple)
}

objPosBST::~objPosBST()
{
    deleteTree(root);
    root = NULL;
    // Destructor
    // Invoke delete tree, then set root to NULL
}

void objPosBST::deleteTree(const TNode* thisNode)
{
	// Delete all nodes in the tree
    // Question from Class - Which Traversal Order should you use for this method?
    //   WARNING - using the wrong one will result in potential heap error.
    //post-order operation
    if(thisNode != NULL){
        deleteTree(thisNode->left);
        deleteTree(thisNode->right);
        delete thisNode;
    }
}

// Public Interface, Implemented
void objPosBST::deleteTree()
{
    deleteTree(root); // recursive call on the private helper function
    root = nullptr;
}

bool objPosBST::isEmptyTree() const
{
    if(root == NULL){
        return true;
    }
    else{
        return false;
    }
    // Check if tree is empty
    //  Really simple, think about how.
}

// Public Interface, Implemented
void objPosBST::printTree() const
{    
    if(root == NULL)
    {
        cout << "[Empty]";
        return;
    }
    printTree(root);  // recursive call on the private helper function
}

void objPosBST::printTree(const TNode* thisNode) const  // private recursive
{
    // Print the entire tree content using **In-Order Traversal**
    if(thisNode != NULL){
        printTree(thisNode->left);
        thisNode->data.printObjPos();
        printTree(thisNode->right);
    }
    // use printObjPos() method in objPos class for formatted print
}

// Public Interface, Implemented
bool objPosBST::isInTree(const objPos &thisPos) const
{
    return isInTree(thisPos, root); // recursive call on the private helper function
}

bool objPosBST::isInTree(const objPos& thisPos, const TNode* thisNode) const
{
    // Check if thisPos in in the tree.
    //  Remember, tree nodes are inserted using the Prefix member of objPos

    // Algorithm Suggestion:
    // 1. if the node is NULL, just return false
    // 2. Otherwise, compare Prefix of the data of the current node
    //    against the Prefix of thisPos 
    //      - If not equal, follow the BST search rules
    //      - If equal, return true
    if(thisNode == NULL){ //eventually get to the leaf
        return false;    
    }
    else if(thisNode->data.getPF() < thisPos.getPF()){
        isInTree(thisPos,thisNode->right);
    }
    else if(thisNode->data.getPF() > thisPos.getPF()){
        isInTree(thisPos,thisNode->left);
    }
    else{
        return true;
    }
    
}
// Public Interface, Implemented
void objPosBST::insert(const objPos &thisPos)
{
    insert(thisPos, root); // recursive call on the private helper function
}

// insert OR update!!
void objPosBST::insert(const objPos &thisPos, TNode* &thisNode)
{
    // Insert objPos as a Node into the BST
    if(thisNode == NULL){
        thisNode = new TNode(thisPos);
    }
    else if(thisNode->data.getPF() < thisPos.getPF()){
        insert(thisPos,thisNode->right);
    }
    else if(thisNode->data.getPF() > thisPos.getPF()){
        insert(thisPos,thisNode->left);
    }
    else{
        int a = thisNode->data.getNum();
        int b = thisPos.getNum();
        thisNode->data.setNum(a+b);
        //identical data has been found,ingored it LOL
    }
    // Check Lecture Notes for general implementation
    //  Hint: Algorithm similar to isInTree.
    // Modification: 
    //   If the node is already in the tree (i.e. Prefix match found)
    //   Add the number member of thisPos to the number member of the objPos data at the node
    //   (DO NOT JUST IGNORE.  ADD NUMBERS!!)
}

const TNode* objPosBST::findMin(const TNode* thisNode) const
{
	// Find the node with the smallest prefix in the subtree from thisNode
    if(thisNode == nullptr){
        return NULL;
    }
    else if(thisNode->left == nullptr){
        return thisNode;
    }
    else{
        findMin(thisNode->left); //recursion strucutre 
    }
    // Used as part of remove() algorithm
    // Check Lecture Notes for implementation
}

void objPosBST::remove(const objPos &thisPos, TNode* &thisNode)
{
	// Remove the node with matching prefix of thisPos from the subtree thisNode
    // *IMPORTANT* Check Lecture Notes for general implementation
    //  Remember the three removal case scenarios
    // Case 1 and 2 both can be handled with one algorithm (Lecture Notes)

    // Case 3 - Delete the node with 2 children
    //   You can use either methods (check lecture notes)
    if(thisNode == NULL){
    }
    else if(thisNode->data.getPF() < thisPos.getPF()){
        remove(thisPos,thisNode->right);
    }
    else if(thisNode->data.getPF() > thisPos.getPF()){
        remove(thisPos,thisNode->left);
    }
    else if(thisNode->left != NULL && thisNode->right != NULL){
        thisNode->data.setPF(findMin(thisNode->right)->data.getPF());
        remove(thisNode->data,thisNode->right); //remove 2 child node, must at bottom lol
    }
    else{
        TNode* garbage = thisNode; //str the temp reg
        if(thisNode->left == NULL){
            thisNode = thisNode->right;
        }
        else{
            thisNode = thisNode->left;
        }
        delete garbage;
    }

}

// Public Interface, Implemented
void objPosBST::remove(const objPos &thisPos)
{
    remove(thisPos, root); // recursive call on the private helper function
}

bool objPosBST::isLeaf(const objPos &thisPos, const TNode* thisNode) const
{
    // Check if thisPos in a Leaf Node.
    //  Remember, tree nodes are inserted using the Prefix member of objPos
    if(thisNode == NULL){
        return false;
    }
    else if(thisNode->data.getPF() < thisPos.getPF()){
        isLeaf(thisPos,thisNode->right);
    }
    else if(thisNode->data.getPF() > thisPos.getPF()){
        isLeaf(thisPos,thisNode->left);
    }
    else 
    {
        if(thisNode->left == NULL && thisNode->right == NULL){
            return true;
        }
        else{
            return false;
        }
    }
}
    // Algorithm Suggestion:
    // 1. if the node is NULL, just return false
    // 2. Otherwise, compare Prefix of the data of the current node
    //    against the Prefix of thisPos
    //      - If not equal, follow the BST search rules
    //      - If equal, check if the node is a leaf node
    // Remember, leaf nodes do not have children nodes

// Public Interface, Implemented
bool objPosBST::isLeaf(const objPos &thisPos) const
{
    return isLeaf(thisPos, root); // recursive call on the private helper function
}

bool objPosBST::findGreater(const int numThreshold, const TNode* thisNode) const
{
    // Determine whether any nodes in the tree has the NUMBER field of objPos data member greater than numThreshold
    // WARNING - this one is not as straightforward.
    // Algorithm Suggestion
    //  1. If tree empty, just return false
    //  2. Recursively check if the any number on the LEFT subtree is greater than numThreshold
    //  3. Recursively check if the any number on the RIGHT subtree is greater than numThreshold
    //  4. Then, check if the number field of the objPos data in the current node is greater than numThreshold
    //  5. If any of the results from item 2, 3, and 4 is TRUE, return true.
    //     Otherwise, return false.
    // HINT:  If you do this right, the algorithm is less than 10 lines.
    if(thisNode == NULL){
        return false;
    }
    else if(thisNode->data.getNum() <= numThreshold){
        findGreater(numThreshold,thisNode->left);
        findGreater(numThreshold,thisNode->right);
    }
    else{
        return true;
    }
}

// Public Interface, Implemented
bool objPosBST::findGreater(const int numThreshold) const
{
    return findGreater(numThreshold, root);
}
