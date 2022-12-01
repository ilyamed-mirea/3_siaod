//
// Created by ilyaMedvedev on 29.11.2022.
//

#ifndef SIAOD_TREE5_H
#define SIAOD_TREE5_H
#include "iostream"

struct Node {
    int key; //groupId
    int data; //number of entry in file
    Node* left;
    Node* right;

    Node(int newLeafData = 0, int newLeafKey = 0);
};

struct Tree {
    Node* head;

    void insert(int newLeafKey, int newLeafData, Node *&parentNode);
    int insert(int newLeafKey, int newLeafData);
    void remove(int leafToRemoveKey, Node *&parentNode, int side = 0);
    int remove(int leafToRemoveKey, int side = 0);
    Node* find(int leafData);
    Node* findLast(Node *currentNode, Node* maxNode);
    void printTree(const std::string& prefix, Node *currentNode, bool isLeft=false);
    int printTree();

    Tree(Node* head = nullptr);
};

#endif //SIAOD_TREE5_H
