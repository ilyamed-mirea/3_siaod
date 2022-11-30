//
// Created by ilyaMedvedev on 29.11.2022.
//

#ifndef SIAOD_TREE_H
#define SIAOD_TREE_H
#include "iostream"

struct Node {
    int data;
    //int key;
    Node* left;
    Node* right;

    Node(int newLeafData);
};

struct Tree {
    Node* head;

    void insert(int newLeafData, Node *parentNode = nullptr, int side = 0);
    void remove(int leafToRemoveData, Node *parentNode = nullptr, int side = 0);
    Node* find(int leafData);
    void removeMax();
    int findSum(Node* currentNode);
    int countLeaves(Node* currentNode);
    void printTree(const std::string& prefix="", Node *currentNode= nullptr, bool isLeft=false);

    Tree(Node* head = nullptr);
};

#endif //SIAOD_TREE_H
