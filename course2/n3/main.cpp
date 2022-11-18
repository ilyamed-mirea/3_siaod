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

const string FILE_NAME = "hash.txt";
const string BIN_FILE_NAME = "bin_hash.bin";

int main() {
    system("chcp 65001");
    fstream file(BIN_FILE_NAME, ios::in | ios::out | ios::binary | ios::trunc);
    file.close();

    testHeshT(BIN_FILE_NAME,FILE_NAME);

    return 0;
}