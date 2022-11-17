//
// Created by 0ilya on 17.11.2022.
//

#include "binaryHashOperator.h"

void fillTableFromBin(HashTable &table, const std::string &binFileName) {
    groupElement entry;
    for (int i=1;i<=table.length;i++) {
        entry = getEntryFromBin(binFileName, i);
        table.insert(entry);
    }
}

void removeEntry(HashTable &table, const std::string &binFileName, int groupId) {
    table.remove(groupId);
    deleteEntryByKey(groupId, binFileName);
}

