//
// Created by ilyaMedvedev on 02.11.2022.
//

#ifndef HASHTABLE_H
#define HASHTABLE_H

struct groupElement {
    int groupId;
    double medianScore;
    int studentCount;
    int predmetId;

    groupElement();

    groupElement(int groupId);

    groupElement(int groupId, double medianScore, int studentCount, int predmetId);
};

struct tableNode {
    int groupId;
    int entryId;
    tableNode *next = nullptr;

    tableNode(int groupId, int entryId, tableNode *next = nullptr);
};

struct HashTable {
    int length;
    int filled;
    tableNode **rows;

    HashTable(int length = 10);

    int insert(groupElement gotElement, int entryId = -1);

    int remove(int groupId);

    tableNode *search(int groupId, int entryId = -1);

    int rehash();

    int print();

    ~HashTable();
};

int hashIndex(int groupId, int length);

#endif //HASHTABLE_H
