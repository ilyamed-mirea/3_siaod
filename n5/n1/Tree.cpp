//
// Created by ilyaMedvedev on 29.11.2022.
//

#include "Tree.h"
#include "iostream"

using namespace std;

void Tree::insert(int newLeafKey, int newLeafData, Node *&parentNode) {
    if (!parentNode) {
        parentNode = new Node(newLeafData, newLeafKey);
    } else if (newLeafKey < parentNode->key) {
        insert(newLeafKey, newLeafData, parentNode->left);
    } else if (newLeafKey > parentNode->key) {
        insert(newLeafKey, newLeafData, parentNode->right);
    }
}

void Tree::remove(int leafToRemoveKey, Node *&parentNode, int side) {
    if (parentNode == nullptr) {
        cout << "Tree is empty" << endl;
        return;
    }
    Node *currentNode = side > 0 ? parentNode->right : side < 0 ? parentNode->left : this->head;
    if (currentNode->key!=leafToRemoveKey && (!currentNode->right || currentNode->right->key < leafToRemoveKey) && (!currentNode->left || currentNode->left->key > leafToRemoveKey)) {
        cout << "No such element" << endl;
        return;
    }
    if (leafToRemoveKey > currentNode->key)
        this->remove(leafToRemoveKey, currentNode, +1);
    else if (leafToRemoveKey < currentNode->key)
        this->remove(leafToRemoveKey, currentNode, -1);
    else if (leafToRemoveKey == currentNode->key) { // currentNode is the node to remove
        if (!currentNode->left && !currentNode->right) { // currentNode has no children
            delete currentNode;
            (side > 0 ? parentNode->right : side == 0 ? this->head : parentNode->left) = nullptr;
        } else if (!currentNode->left || !currentNode->right) { // currentNode has one child
            Node *&children = currentNode->left != nullptr ? currentNode->left : currentNode->right;
            currentNode->data = children->data;
            currentNode->key = children->key;
            currentNode->right = children->right;
            currentNode->left = children->left;
            delete children;
        } else { // currentNode has two children
            if (currentNode->right->left == nullptr) { // parentNode->right has no left child
                currentNode->data = currentNode->right->data;
                currentNode->key = currentNode->right->key;
                currentNode->right = currentNode->right->right;
            } else {
                Node *leftmost = currentNode->right;
                while (leftmost->left != nullptr) { // find the leftmost leaf of the right subtree
                    leftmost = leftmost->left;
                }
                int tempData = leftmost->data;
                int tempKey = leftmost->key;
                remove(leftmost->key);
                currentNode->data = tempData;
                currentNode->key = tempKey;
            }
        }
    }
}


Node *Tree::find(int leafKey) {
    Node *currentNode = this->head;
    while (currentNode) {
        if (leafKey == currentNode->key) return currentNode;
        else if (leafKey > currentNode->key) currentNode = currentNode->right;
        else if (leafKey < currentNode->key) currentNode = currentNode->left;
    }
    return nullptr;
}


void Tree::printTree(const std::string &prefix, Node *currentNode, bool isLeft) {
    if (currentNode != nullptr) {
        std::cout << prefix;
        std::cout << (isLeft ? "R--" : "L--");
        // print the value of the node
        std::cout << currentNode->key << std::endl;
        // enter the next tree level - left and right branch
        printTree(prefix + (isLeft ? "|   " : "    "), currentNode->right, true);
        printTree(prefix + (isLeft ? "|   " : "    "), currentNode->left, false);
    }
}

int Tree::printTree() {
    this->printTree("", this->head, false);
    return 0;
}

Tree::Tree(Node *head) {
    this->head = head;
}

int Tree::insert(int newLeafKey, int newLeafData) {
    this->insert(newLeafKey, newLeafData, this->head);
    return 0;
}

int Tree::remove(int leafToRemoveKey) {
    remove(leafToRemoveKey, this->head);
    return 0;
}

Node *Tree::findLast(Node *currentNode, Node* maxNode) {
    //find node with maximum data
    if (!currentNode) return maxNode;
    else if (!currentNode->left && !currentNode->right) return currentNode;
    Node *maxLeft = this->findLast(currentNode->left, maxNode);
    Node *maxRight = this->findLast(currentNode->right, maxNode);
    if (maxLeft->data > maxRight->data) {
        if (maxLeft->data > maxNode->data) {
            maxNode = maxLeft;
        } else {
            maxNode = currentNode;
        }
    } else {
        if (maxRight->data > currentNode->data) {
            maxNode = maxRight;
        } else {
            maxNode = currentNode;
        }
    }
    return maxNode;
}

Node::Node(int newLeafData, int newLeafKey) {
    this->key = newLeafKey;
    this->data = newLeafData;
    this->left = nullptr;
    this->right = nullptr;
}
