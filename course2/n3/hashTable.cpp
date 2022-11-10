#include <iostream>
#include "hashTable.h"
using namespace std;

struct groupElement {
    int groupId;
    int entryId;
    double medianScore;
    int studentCount;
    string predmet;
    groupElement *next;

    groupElement() {
        srand(time(nullptr));
        groupId = rand() % 100;
        medianScore = 4.7;
        studentCount = 0;
        predmet = "none";
        next = nullptr;
    }
    groupElement(int groupId, double medianScore, int studentCount, string predmet, int entryId) {
        this->groupId = groupId;
        this->medianScore = medianScore;
        this->studentCount = studentCount;
        this->entryId = entryId;
        this->predmet = predmet;
        this->next = nullptr;
    }
};

//hash get add remove print rehash
struct HashTable {
    int length;
    int filled;
    groupElement **rows;
    //int insertedCount; //колво вставленных ключей
    //int deletedCount; //колво удаленных ключей
    HashTable(int length=10) {
        *rows = new groupElement[length];
        this->length = length;
        this->filled = 0;
        //insertedCount = 0;
        //deletedCount = 0;
    }
};

//хеш-функция
int hashIndex(int groupId, int length) {
    return groupId % length;
}

//вставка без рехеширования
int insertInHashTable(int groupId, int offset, HashTable &table) {
    int i = hashIndex(groupId, table.length);
    groupElement currentElement = *table.rows[i]; //head
    groupElement *newElement;
    int entryId = 1;
    /*if (currentElement.studentCount ==0) //change head
        entryId=1;
    else entryId=0;*/
    while (currentElement.next != nullptr) {
        entryId++;
        currentElement = *currentElement.next;
    }
    entryId++; //new after last
    if (i >= table.length)
        return 1;
    else {
        int groupId = 0; double medianScore = 0; int studentCount = 0;
        cin >> groupId >> medianScore >> studentCount;
        string predmet;
        getline(cin,predmet);
        newElement = new groupElement(groupId, medianScore, studentCount, predmet, entryId);
        currentElement.next = newElement;
        table.filled++;
        //currentElement.offset = offset;
        //currentElement.isOpen = false;
        //table.insertedCount++;
        return 0;
    }
}

int search(HashTable &table, int groupId) {
    return -1;
    /*int i = hashIndex(groupId, table.length);
    groupElement *item = &table.rows[i];
    while (i < table.length && item->groupId != groupId &&
           (
                   (!item->isOpen && !item->isDeleted) //ячейка закрыта и не удалена
                   ||
                   (item->isOpen && item->isDeleted) //ячейка открыта и удалена
           )) {
        item = &table.rows[++i];
    }
    if (item->isOpen && !item->isDeleted) {
        return -1;
    }
    return item->offset;*/
}

//вывод таблицы
void printHashTable(HashTable table) {
    for (int i = 0; i < table.length; i++) {
        groupElement *currentElement = table.rows[i];
        while (currentElement->next!=nullptr) {
            cout << i << ' ' << currentElement->groupId << ' ' << endl;
            currentElement = currentElement->next;
        }
    }
}
