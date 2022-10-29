#include <iostream>
#include <fstream>
#include <vector>
#include "istream"
#include <string>
#include <unistd.h>
#include <filesystem>

#define SHIFT 5
#define MASK 0x1F

#include <cmath>

using namespace std;

const bool testMode = true;

struct typeitem {
    int key = 0;
    int offset = 0;
    bool isOpen = true; //свободна
    bool isDeleted = false; //не удалялась
};

struct HashTable {
    int length = 10;
    typeitem *rows;
    int insertedCount; //колво вставленных ключей
    int deletedCount; //колво удаленных ключей
    //void createHashTable() {
    HashTable() {
        rows = new typeitem[length];
        insertedCount = 0;
        deletedCount = 0;
    }
};

//хеш-функция
int hashIndex(int key, int length) {
    return key % length;
}

int collision(int key, int length) {
    return 0;
}

//вставка без рехеширование
int insertInHashTable(int key, int offset, HashTable &table) {
    int i = hashIndex(key, table.length);
    while (i < table.length && !table.rows[i].isOpen)
        i++;
    typeitem *item = &table.rows[i];
    if (i >= table.length)
        return 1;
    else {
        item->key = key;
        item->offset = offset;
        item->isOpen = false;
        table.insertedCount++;
        return 0;
    }

}

int search(HashTable &table, int key) {
    int i = hashIndex(key, table.length);
    typeitem *item = &table.rows[i];
    while (i < table.length && item->key != key &&
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
    return item->offset;
}

//вывод таблицы
void outHashTable(HashTable table) {
    for (int i = 0; i < table.length; i++) {
        cout << i << ' ' << table.rows[i].key << ' ' << table.rows[i].offset << endl;
    }
}

int main() {
    system("chcp 65001");

    HashTable table;
    insertInHashTable(105, 1, table);
    insertInHashTable(102, 5, table);
    insertInHashTable(107, 3, table);
    insertInHashTable(117, 2, table);
    insertInHashTable(205, 4, table);
    insertInHashTable(202, 7, table);
    insertInHashTable(113, 6, table);
    insertInHashTable(109, 8, table);

    search(table, 117);

    outHashTable(table);
}