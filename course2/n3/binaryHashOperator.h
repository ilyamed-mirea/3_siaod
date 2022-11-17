
#ifndef SIAOD_BINARYHASHOPERATOR_H
#define SIAOD_BINARYHASHOPERATOR_H

#include "hashTable.h"
#include "binary.h"
#include "iostream"

void fillTableFromBin(HashTable &table, const std::string &binFileName);
void removeEntry(HashTable &table, const std::string &binFileName, int groupId);


#endif //SIAOD_BINARYHASHOPERATOR_H
