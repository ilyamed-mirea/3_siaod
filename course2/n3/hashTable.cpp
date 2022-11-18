#include <iostream>
#include "hashTable.h"

using namespace std;

groupElement::groupElement() {
    srand(time(nullptr));
    groupId = rand() % 100;
    medianScore = -1;
    studentCount = -1;
    predmetId = -1;
}

groupElement::groupElement(int groupId) {
    this->groupId = groupId;
    this->medianScore = -1;
    this->studentCount = -1;
    this->predmetId = -1;
}

groupElement::groupElement(int groupId, double medianScore, int studentCount, int predmetId) {
    this->groupId = groupId;
    this->medianScore = medianScore;
    this->studentCount = studentCount;
    //this->entryId = entryId;
    this->predmetId = predmetId;
}

tableNode::tableNode(int groupId, int entryId, tableNode *next) {
    this->groupId = groupId;
    this->entryId = entryId;
    this->next = next;
}

HashTable::HashTable(int length) {
    rows = new tableNode *[length]{nullptr};
    this->length = length;
    this->filled = 0;
}

HashTable::~HashTable() {
    this->length = 0;
    this->filled = 0;
    rows = nullptr;
}

//хеш-функция
int hashIndex(int groupId, int length) {
    return groupId % length;
}

int HashTable::insert(groupElement gotElement, int entryId) {
    int i = hashIndex(gotElement.groupId, this->length);
    tableNode *currentNode = this->rows[i]; //head
    while (currentNode && currentNode->next != nullptr)
        currentNode = currentNode->next;
    tableNode *newNode = new tableNode(gotElement.groupId, entryId);
    if (currentNode == nullptr)
        this->rows[i] = newNode;
    else
        currentNode->next = newNode;
    this->filled++;
    if (this->filled / this->length >= 0.75)
        this->rehash();
    return 0;
}

int HashTable::rehash() {
    int oldLength = this->length;
    this->length *= 2;
    HashTable newTable(this->length);
    for (int i = 0; i < oldLength; i++) {
        tableNode *temp = this->rows[i];
        if (temp) {
            do {
                int i = hashIndex(temp->groupId, this->length);
                tableNode *x = newTable.rows[i];
                if (x==nullptr)
                    newTable.rows[i] = temp;
                else {
                    while (x->next) {
                        x = x->next;
                    }
                    x->next = temp;
                }
                temp = temp->next;
            } while (temp);
        }
    }
    for (int i = 0; i < this->length; i++) {
        this->rows[i] = newTable.rows[i];
    }
    return 0;
}

tableNode *HashTable::search(int groupId, int entryId) {
    int i = hashIndex(groupId, this->length);
    tableNode *node = this->rows[i];
    while (node && node->groupId != groupId && (entryId == -1 || node->entryId != entryId)) {
        node = node->next;
    }
    if (node->groupId == groupId && (entryId == -1 || node->entryId == entryId))
        return node;
    else return nullptr;
}

//вывод таблицы
int HashTable::print() {
    cout << "go\n" << endl;
    for (int i = 0; i < this->length; i++) {
        tableNode *currentElement = rows[i];
        cout << i << ":";
        while (currentElement) {
            cout << ' ' << currentElement->groupId << ' ';
            currentElement = currentElement->next;
        }
        cout << endl;
    }
    return 0;
}

int HashTable::remove(int groupId) {
    tableNode *currentNode = this->search(groupId);
    tableNode *prevNode = this->search(groupId, currentNode->entryId - 1);
    tableNode *nextNode = this->search(groupId, currentNode->entryId + 1);
    prevNode->next = nextNode;
    return 0;
}
