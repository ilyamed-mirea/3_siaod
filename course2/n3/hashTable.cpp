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
    HashTable(int length=10) {
        rows = new groupElement*[length]{nullptr};
        this->length = length;
        this->filled = 0;
        //insertedCount = 0;
        //deletedCount = 0;
    }
    int insert(int groupId);
    int rehash();
    int print();
    ~HashTable() {
        rows = nullptr;
    }
};

//хеш-функция
int hashIndex(int groupId, int length) {
    return groupId % length;
}

//вставка без рехеширования
int HashTable::insert(int groupId) {
    int i = hashIndex(groupId, this->length);
    groupElement *currentElement = this->rows[i]; //head
    int entryId = 1;
    /*if (currentElement.studentCount ==0) //change head
        entryId=1;
    else entryId=0;*/
    while (currentElement && currentElement->next != nullptr) {
        entryId++;
        currentElement = currentElement->next;
    }
    entryId++; //new after last
    if (i >= this->length)
        return 1;
    else {
        int groupId = 0; double medianScore = 0; int studentCount = 0;
        cin >> groupId >> medianScore >> studentCount;
        string predmet;
        getline(cin,predmet);
        getline(cin,predmet);
        groupElement *newElement = new groupElement(groupId, medianScore, studentCount, predmet, entryId);
        currentElement->next = newElement;
        this->filled++;
        //if (this->filled/this->length>=0.75)
        //    this->rehash();
        return 0;
    }
}

int HashTable::rehash() {
    return 0;
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
int HashTable::print() {
    cout << "go\n"<<endl;
    for (int i = 0; i < this->length; i++) {
        groupElement *currentElement = this->rows[i];
        while (currentElement->next!=nullptr) {
            cout << i << ' ' << currentElement->groupId << ' ' << endl;
            currentElement = currentElement->next;
        }
    }
}
