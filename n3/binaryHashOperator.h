
#ifndef SIAOD_BINARYHASHOPERATOR_H
#define SIAOD_BINARYHASHOPERATOR_H

#include "hashTable.h"
#include "binary.h"

void fillTableFromBin(HashTable &table, const std::string &binFileName);
void removeEntry(HashTable &table, const std::string &binFileName, int groupId);
groupElement findInBinByKey(HashTable &table, int groupId, const std::string &binFileName);
void addEntry(HashTable &table, const std::string &binFileName);
void milTest(HashTable &table,const std::string &binFileName);
int testHeshT(const std::string &binFileName, const std::string &textFileName);
#endif //SIAOD_BINARYHASHOPERATOR_H
