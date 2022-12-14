#include <iostream>
#include "hashTable.h"

using namespace std;


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
    //удалить все значения листа сначала
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
    tableNode **oldRows = this->rows;
    this->rows = new tableNode *[this->length *= 2]{nullptr};
    this->filled = 0;
    for (int i = 0; i < oldLength; i++) {
        tableNode *currentNode = oldRows[i];
        while (currentNode) {
            this->insert(groupElement(currentNode->groupId), currentNode->entryId);
            currentNode = currentNode->next;
        }
        delete[] currentNode;
    }
    delete[] oldRows;
    return 0;
}

tableNode *HashTable::search(int groupId, int entryId, int params) {
    int i = hashIndex(groupId, this->length);
    tableNode *node = this->rows[i];
    while (node && node->groupId != groupId && (params != -1 || node->next->groupId != groupId) &&
           (entryId == -1 || node->entryId != entryId))
        node = node->next;
    if (params == +1)
        return node->next;
    if (params == -1 && node->groupId == groupId)
        return nullptr;
    if ((node->groupId == groupId || params != 0) && (entryId == -1 || node->entryId == entryId))
        return node;
    else return nullptr;
}

//вывод таблицы
int HashTable::print() {
    cout << "print:\n";
    for (int i = 0; i < this->length; i++) {
        tableNode *currentElement = rows[i];
        cout << i << ":";
        while (currentElement) {
            cout << " (groupId: " << currentElement->groupId << " entryId: " << currentElement->entryId << ')';
            currentElement = currentElement->next;
        }
        cout << endl;
        delete[] currentElement;
    }
    return 0;
}

int HashTable::remove(int groupId) {
    tableNode *prevNode = this->search(groupId, -1, -1);
    tableNode *nextNode = this->search(groupId, -1, +1);
    //удалить из среднего
    if (!prevNode) {
        int i = hashIndex(groupId, this->length);
        this->rows[i] = nextNode;
    } else prevNode->next = nextNode;
    return 0;
}
