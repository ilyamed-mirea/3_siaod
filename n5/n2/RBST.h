//
// Created by ilyaMedvedev on 29.11.2022.
//

#ifndef SIAOD_RBST_H
#define SIAOD_RBST_H

#include "iostream"

enum Color {
    RED, BLACK
};

struct Node {
    int key; //groupId
    int data; //number of entry in file
    Color color;
    Node *left, *right, *parent;

    Node(int newLeafData = 0, int newLeafKey = 0, Node *parent = nullptr, Color newLeafColor = RED);
};

struct Tree {
    Node *head;
    int rotatingCount;

    Node* insert(int newLeafKey, int newLeafData, Node *&parentNode);

    int insert(int newLeafKey, int newLeafData);

    Node* remove(int leafToRemoveKey, Node *&currentNode);

    int remove(int leafToRemoveKey);

    Node *find(int leafData);

    Node *findLast(Node *currentNode, Node *maxNode);

    void printTree(const std::string &prefix, Node *currentNode, bool isLeft = false);

    int printTree();

    void correctTree(Node *node);

    void rotateLeft(Node *node);

    void rotateRight(Node *node);

    Tree(Node *head = nullptr);
};

#endif //SIAOD_RBST_H
