#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unistd.h>
#include <cmath>
#include "hashTable.cpp"
#include "binary.h"

using namespace std;

const bool testMode = true;

int main() {
    system("chcp 65001");

    HashTable table;
    insertInHashTable(105, 1, table);
    insertInHashTable(102, 5, table);
    insertInHashTable(107, 3, table);
    insertInHashTable(117, 2, table);
    insertInHashTable(105, 4, table);
    insertInHashTable(102, 7, table);

    //search(table, 117);

    printHashTable(table);
}