#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unistd.h>
#include <cmath>

#include "hashTable.cpp"
#include "binary.cpp"
#include "binaryHashOperator.cpp"

using namespace std;

const bool testMode = true;
const string FILE_NAME = "hash.txt";
const string BIN_FILE_NAME = "bin_hash.bin";

int main() {
    system("chcp 65001");

    createTxtFile(FILE_NAME);
    createBinFromTxt(FILE_NAME, BIN_FILE_NAME);
    HashTable table(10);
    fillTableFromBin(table,BIN_FILE_NAME);
    //search(table, 117);

    //table.print();
}