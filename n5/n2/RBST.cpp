//
// Created by ilyaMedvedev on 29.11.2022.
//

#include "RBST.h"
#include "iostream"

using namespace std;

Node *Tree::insert(int newLeafKey, int newLeafData, Node *&parentNode) {
    if (!parentNode) {
        parentNode = parentNode == head ? new Node(newLeafData, newLeafKey, nullptr, BLACK) : new Node(newLeafData,
                                                                                                       newLeafKey);
        return parentNode;
    } else if (newLeafKey < parentNode->key) {
        if (parentNode->left)
            return insert(newLeafKey, newLeafData, parentNode->left);
        else {
            parentNode->left = new Node(newLeafData, newLeafKey, parentNode);
            return parentNode->left;
        }
    } else if (newLeafKey > parentNode->key) {
        if (parentNode->right)
            return insert(newLeafKey, newLeafData, parentNode->right);
        else {
            parentNode->right = new Node(newLeafData, newLeafKey, parentNode);
            return parentNode->right;
        }
    }
}

Node* Tree::remove(int leafToRemoveKey, Node *&currentNode) {
    if (currentNode == nullptr) {
        cout << "Tree is empty" << endl;
        return nullptr;
    }
    if (currentNode->key != leafToRemoveKey && (!currentNode->right || currentNode->right->key < leafToRemoveKey) &&
        (!currentNode->left || currentNode->left->key > leafToRemoveKey)) {
        cout << "No such element" << endl;
        return nullptr;
    }
    if (leafToRemoveKey > currentNode->key)
        return this->remove(leafToRemoveKey, currentNode->right);
    else if (leafToRemoveKey < currentNode->key)
        return this->remove(leafToRemoveKey, currentNode->left);
    else if (leafToRemoveKey == currentNode->key) { // currentNode is the node to remove
        if (!currentNode->left && !currentNode->right) { // currentNode has no children
            Node *&parentNode = currentNode->parent;
            (currentNode->key==parentNode->left->key ? parentNode->left : parentNode->right) = nullptr;
            delete currentNode;
            return parentNode;
        } else if (!currentNode->left || !currentNode->right) { // currentNode has one child
            Node *&children = currentNode->left ? currentNode->left : currentNode->right;
            currentNode->data = children->data;
            currentNode->key = children->key;
            currentNode->right = children->right;
            currentNode->left = children->left;
            delete children;
            return currentNode;
        } else { // currentNode has two children
            if (currentNode->right->left == nullptr) { // parentNode->right has no left child
                currentNode->data = currentNode->right->data;
                currentNode->key = currentNode->right->key;
                currentNode->right = currentNode->right->right;
                return currentNode;
            } else {
                Node *leftmost = currentNode->right;
                while (leftmost->left != nullptr) { // find the leftmost leaf of the right subtree
                    leftmost = leftmost->left;
                }
                int tempData = leftmost->data;
                int tempKey = leftmost->key;
                remove(leftmost->key, this->head);
                currentNode->data = tempData;
                currentNode->key = tempKey;
                return currentNode;
            }
        }
    }
    return currentNode;
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
        std::cout << "(" << (currentNode->color == RED ? "RED" : "BLACK") << ")" << currentNode->key << std::endl;
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
    this->rotatingCount = 0;
}

int Tree::insert(int newLeafKey, int newLeafData) {
    Node *node = this->insert(newLeafKey, newLeafData, this->head);
    this->correctTree(node);
    return 0;
}

void Tree::correctTree(Node *node) {
    while (node != head && node->parent->color == RED) {
        if (node->parent == node->parent->parent->left) {
            Node *uncle = node->parent->parent->right;
            if (uncle && uncle->color == RED) {
                uncle->color = BLACK;
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else { // uncle is black
                if (node == node->parent->right) {
                    node = node->parent;
                    this->rotateLeft(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                this->rotateRight(node->parent->parent);
            }
        } else {
            Node *uncle = node->parent->parent->left;
            if (uncle && uncle->color == RED) {
                uncle->color = BLACK;
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else { // uncle is black
                if (node == node->parent->left) {
                    node = node->parent;
                    this->rotateRight(node); //rotate left?
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                this->rotateLeft(node->parent->parent);
            }
        }
    }
    head->color = BLACK; // root is always black
}

int Tree::remove(int leafToRemoveKey) {
    Node *rem = remove(leafToRemoveKey, this->head);
    correctTree(rem);
    return 0;
}

Node *Tree::findLast(Node *currentNode, Node *maxNode) {
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

void Tree::rotateLeft(Node *node) {
    Node *right = node->right;
    node->right = right->left;
    if (right->left != nullptr) {
        right->left->parent = node;
    }
    right->parent = node->parent;
    if (node->parent == nullptr) {
        this->head = right;
    } else if (node == node->parent->left) {
        node->parent->left = right;
    } else {
        node->parent->right = right;
    }
    right->left = node;
    node->parent = right;
    this->rotatingCount++;
}

void Tree::rotateRight(Node *node) {
    Node *left = node->left;
    node->left = left->right;
    if (left->right != nullptr) {
        left->right->parent = node;
    }
    left->parent = node->parent;
    if (node->parent == nullptr) {
        this->head = left;
    } else if (node == node->parent->right) {
        node->parent->right = left;
    } else {
        node->parent->left = left;
    }
    left->right = node;
    node->parent = left;
    this->rotatingCount++;
}

Node::Node(int newLeafData, int newLeafKey, Node *parent, Color newLeafColor) {
    this->key = newLeafKey;
    this->data = newLeafData;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = parent;
    this->color = newLeafColor;
}
