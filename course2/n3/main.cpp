#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unistd.h>
#include <cmath>

#include "hashTable.cpp"
#include "hashTable.h"
#include "binary.h"

using namespace std;

const bool testMode = true;

int main() {
    system("chcp 65001");

    HashTable table(10);
    int code = table.insert(105);
    cout<<"inserted\n";
    table.insert(102);
    table.insert(107);
    table.insert(117);
    table.insert(105);
    table.insert(102);

    cout<<"inserted\n";

    //search(table, 117);

    table.print();
}