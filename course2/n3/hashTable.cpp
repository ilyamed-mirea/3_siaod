#include <iostream>

using namespace std;

struct groupElement {
    int groupId;
    int entryCounter;
    double medianScore;
    int studentCount;
    groupElement *next;

    groupElement() {
        srand(time(nullptr));
        groupId = rand() % 100;
        medianScore = 4.7;
        studentCount = 28;
        next = nullptr;
    }
    groupElement(int groupId, double medianScore, int studentCount) {
        this->groupId = groupId;
        this->medianScore = medianScore;
        this->studentCount = studentCount;
    }
};

//hash get add remove print rehash
struct HashTable {
    int length;
    groupElement **rows;
    //int insertedCount; //колво вставленных ключей
    //int deletedCount; //колво удаленных ключей
    HashTable(int length=10) {
        *rows = new groupElement[length];
        this->length = length;
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
    int entryId;
    if (table.rows[i])
        entryId=1;
    else entryId=0;
    while (currentElement.next != nullptr) {
        entryId++;
        currentElement = *currentElement.next;
    }
    entryId++;
    if (i >= table.length)
        return 1;
    else {
        int groupId = 0; double medianScore = 0; int studentCount = 0;
        cin >> groupId >> medianScore >> studentCount;
        newElement = new groupElement(groupId, medianScore, studentCount);
        currentElement.next = newElement;
        //currentElement.offset = offset;
        //currentElement.isOpen = false;
        //table.insertedCount++;
        return 0;
    }
}

int search(HashTable &table, int groupId) {
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
