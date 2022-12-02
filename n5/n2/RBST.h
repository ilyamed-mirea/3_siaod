//
// Created by ilyaMedvedev on 29.11.2022.
//

#ifndef SIAOD_RBST_H
#define SIAOD_RBST_H

#include "iostream"

enum Color {
    RED, BLACK
};

struct RBSTNode {
    int key; //groupId
    int data; //number of entry in file
    Color color;
    RBSTNode *left, *right, *parent;

    RBSTNode(int newLeafData = 0, int newLeafKey = 0, RBSTNode *parent = nullptr, Color newLeafColor = RED);
};

struct RBSTTRee {
    RBSTNode *head;
    int rotatingCount;

    RBSTNode* insert(int newLeafKey, int newLeafData, RBSTNode *&parentNode);

    int insert(int newLeafKey, int newLeafData);

    RBSTNode* remove(int leafToRemoveKey, RBSTNode *&currentNode);

    int remove(int leafToRemoveKey);

    RBSTNode *find(int leafKey);

    RBSTNode *findLast(RBSTNode *currentNode, RBSTNode *maxNode);

    void printTree(const std::string &prefix, RBSTNode *currentNode, bool isLeft = false);

    int printTree();

    void correctTree(RBSTNode *node);

    void rotateLeft(RBSTNode *node);

    void rotateRight(RBSTNode *node);

    RBSTTRee(RBSTNode *head = nullptr);
};

#endif //SIAOD_RBST_H
