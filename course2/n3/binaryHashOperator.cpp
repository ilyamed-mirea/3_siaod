//
// Created by 0ilya on 17.11.2022.
//

#include "binaryHashOperator.h"
#include "binary.h"

void fillTableFromBin(HashTable &table, const std::string &binFileName) {
    groupElement entry;
    for (int i = 0; i < getFileLength(binFileName); i++) {
        entry = getEntryFromBin(binFileName, i);
        table.insert(entry, i);
    }
}

void removeEntry(HashTable &table, const std::string &binFileName, int groupId) {
    table.remove(groupId);
    deleteEntryByKey(groupId, binFileName);
}

groupElement findInBinByKey(HashTable &table, int groupId) {
    tableNode *foundInTable = table.search(groupId);
    groupElement res;
    return res;
}


