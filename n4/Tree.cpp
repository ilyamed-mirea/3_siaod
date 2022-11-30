//
// Created by ilyaMedvedev on 29.11.2022.
//

#include "Tree.h"
#include "iostream"

using namespace std;

void Tree::insert(int newLeafData, Node *parentNode, int side) {
    if (head == nullptr) {
        head = new Node(newLeafData);
        return;
    }
    if (parentNode == nullptr) {
        parentNode = head;
    }
    if (newLeafData < parentNode->data) {
        if (parentNode->left == nullptr) {
            parentNode->left = new Node(newLeafData);
            return;
        }
        insert(newLeafData, parentNode->left, 0);
    } else if (newLeafData > parentNode->data) {
        if (parentNode->right == nullptr) {
            parentNode->right = new Node(newLeafData);
            return;
        }
        insert(newLeafData, parentNode->right, 1);
    } /*else { //newLeafData == parentNode->data
        parentNode->key = newLeafKey; //?
    }*/
}

void Tree::remove(int leafToRemoveData, Node *parentNode, int side) {
    if (head == nullptr) {
        cout << "Tree is empty" << endl;
        return;
    }
    if (parentNode == nullptr) {
        parentNode = head;
    }
    Node *currentNode = side > 0 ? parentNode->right : side < 0 ? parentNode->left : this->head;
    if (leafToRemoveData > currentNode->data)
        this->remove(leafToRemoveData, currentNode, +1);
    else if (leafToRemoveData < currentNode->data)
        this->remove(leafToRemoveData, currentNode, -1);
    else if (leafToRemoveData == currentNode->data) { // currentNode is the node to remove
        if (!currentNode->left && !currentNode->right) { // currentNode has no children
            delete currentNode;
            (side > 0 ? parentNode->right : side == 0 ? this->head : parentNode->left) = nullptr;
        } else if (!currentNode->left || !currentNode->right) { // currentNode has one child
            Node *children = currentNode->left != nullptr ? currentNode->left : currentNode->right;
            currentNode->data = children->data;
            currentNode->right = children->right;
            currentNode->left = children->left;
            delete children;
        } else { // currentNode has two children
            if (currentNode->right->left == nullptr) { // parentNode->right has no left child
                currentNode->data = currentNode->right->data;
                currentNode->right = currentNode->right->right;
            } else {
                Node *currentNode = parentNode->right;
                while (currentNode->left != nullptr) { // find the leftmost leaf of the right subtree
                    currentNode = currentNode->left;
                }
                int temp = currentNode->data;
                remove(currentNode->data, head, 0);
                parentNode->data = temp;
            }
        }
    }
}

Node *Tree::find(int leafData) {
    Node *currentNode = this->head;
    while (currentNode) {
        if (leafData == currentNode->data) return currentNode;
        else if (leafData > currentNode->data) currentNode = currentNode->right;
        else if (leafData < currentNode->data) currentNode = currentNode->left;
    }
    return nullptr;
}

void Tree::removeMax() {
    Node *currentNode = this->head;
    while (currentNode->right) {
        currentNode = currentNode->right;
    }
    this->remove(currentNode->data);
}

int Tree::findSum(Node *currentNode) {
    if (!currentNode) return 0;
    int sum = 0;
    sum += this->findSum(currentNode->left);
    sum += currentNode->data;
    sum += this->findSum(currentNode->right);
    return sum;
}

int Tree::countLeaves(Node *currentNode) {
    if (!currentNode) return 0;
    else if (!currentNode->left && !currentNode->right) return 1;
    return this->countLeaves(currentNode->left) + this->countLeaves(currentNode->right);
}

void Tree::printTree(const std::string &prefix, Node *currentNode, bool isLeft) {
    if (currentNode != nullptr) {
        std::cout << prefix;
        std::cout << (isLeft ? "|--" : "L--");
        // print the value of the node
        std::cout << currentNode->data << std::endl;
        // enter the next tree level - left and right branch
        printTree(prefix + (isLeft ? "|   " : "    "), currentNode->right, true);
        printTree(prefix + (isLeft ? "|   " : "    "), currentNode->left, false);
    }
}

Tree::Tree(Node *head) {
    this->head = head;
}

Node::Node(int newLeafData) {
    this->data = newLeafData;
    this->left = nullptr;
    this->right = nullptr;
}
