//
// Created by ilyaMedvedev on 02.11.2022.
//

#ifndef SIAOD_HASHTABLE_H
#define SIAOD_HASHTABLE_H

struct groupElement;
struct HashTable;
int hashIndex(int groupId, int length);
int insertInHashTable(int groupId, int offset, HashTable &table);
void printHashTable(HashTable table);

#endif //SIAOD_HASHTABLE_H
