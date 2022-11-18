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

int testHeshT(const std::string &BIN_FILE_NAME, const std::string &FILE_NAME) {
    HashTable table(10);
    tableNode *node;
    groupElement *elem;

    int num;
    while (1) {
        cout << " Operations:" << endl;
        cout << " 1. Create default TXT file" << endl;
        cout << " 2. Create BIN file from TXT file" << endl;
        cout << " 3. Create hashtable" << endl;
        cout << " 4. Fill hashtable from BIN file" << endl;
        cout << " 5. Print hashtable" << endl;
        cout << " 6. Insert in hashTable" << endl;
        cout << " 7. Remove from hashTable" << endl;
        cout << " 8. Rehash hashTable" << endl;
        cout << " 9. Find element in hashTable" << endl;
        cout << " 10. Remove from hashTable and BIN" << endl;
        cout << " 11. Find element by key" << endl;
        cout << " 0. EXIT" << endl;
        cout << "numPunkt=";
        cin >> num;
        switch (num) {
            case 1:
                createTxtFile(FILE_NAME);
                break;
            case 2: {
                createBinFromTxt(FILE_NAME, BIN_FILE_NAME);
                break;
            }
            case 3:
                cout << "Введите размер таблицы или 0 для автоматического создания" << endl;
                int tableLength;
                cin >> tableLength;
                if (tableLength <= 0)
                    tableLength = getFileLength(BIN_FILE_NAME);
                table = *(new HashTable(tableLength));
                break;
            case 4:
                fillTableFromBin(table, BIN_FILE_NAME);
                break;
            case 5:
                table.print();
                break;
            case 6:
                int groupId1; double medianScore; int studentCount; int predmetId;
                cin >> groupId1 >> medianScore >> studentCount >> predmetId;
                elem = new groupElement(groupId1, medianScore,studentCount,predmetId);
                table.insert(*elem);
                break;
            case 7:
                int groupId2;
                cin >> groupId2;
                table.remove(groupId2);
                break;
            case 8:
                table.rehash();
                break;
            case 9:
                int groupId3;
                cin >> groupId3;
                node = table.search(groupId3);
                cout << node->groupId << " " << node->entryId << endl;
                break;
            case 10:
                int groupId4;
                cin >> groupId4;
                removeEntry(table, BIN_FILE_NAME, groupId4);
                break;
            case 11:
                int groupId5;
                cin >> groupId5;
                *elem = findInBinByKey(table,groupId5);
                cout << elem->groupId << endl;
                break;
            case 0:
                exit(0);
            default:
                break;
        }
    }
}

