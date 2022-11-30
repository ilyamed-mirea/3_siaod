//
// Created by 0ilya on 17.11.2022.
//

#include "binaryHashOperator.h"
#include "binary.h"
#include <ctime>

void fillTableFromBin(HashTable &table, const std::string &binFileName) {
    groupElement entry;
    for (int i = 0; i < getFileLength(binFileName); i++) {
        entry = getEntryFromBin(binFileName, i);
        table.insert(entry, i);
    }
}

tableNode *findLastElementInTable(HashTable &table) {
    tableNode *last = new tableNode(0, -1, nullptr);
    for (int i = 0; i < table.length; i++) {
        tableNode *currentElement = table.rows[i];
        while (currentElement) {
            if (currentElement->entryId > last->entryId) {
                last = currentElement;
            }
            currentElement = currentElement->next;
        }
        delete[] currentElement;
    }
    return last;
}

void removeEntry(HashTable &table, const std::string &binFileName, int groupId) {
    tableNode *node = findLastElementInTable(table);
    table.print();
    table.remove(groupId);
    int newEntryId = deleteEntryByKey(groupId, binFileName);
    node->entryId = newEntryId;
    table.print();
}

void addEntry(HashTable &table, const std::string &binFileName) {
    cout << "write groupId, medianScore, studentCount, predmetId" << endl;
    int groupId1;
    double medianScore;
    int studentCount;
    int predmetId;
    cin >> groupId1 >> medianScore >> studentCount >> predmetId;
    groupElement elem(groupId1, medianScore, studentCount, predmetId);
    addEntryInBin(binFileName,elem);
    table.insert(elem, getFileLength(binFileName)-1);
}

groupElement findInBinByKey(HashTable &table, int groupId, const std::string &binFileName) {
    tableNode *foundInTable = table.search(groupId);
    groupElement res = getEntryFromBin(binFileName, foundInTable->entryId);
    return res;
}

void milTest(HashTable &table,const std::string &binFileName) {
    HashTable newTable(1000000);
    for (int i=0;i<1000000;i++){
        table.insert(groupElement(i,0,0,0),i);
    }
    unsigned int start_time =  clock(); // начальное время
    tableNode *node = table.search(0);
    unsigned int end_time = clock(); // конечное время
    unsigned int search_time1 = end_time - start_time;
    start_time =  clock(); // начальное время
    node = table.search(1000000-1);
    end_time = clock(); // конечное время
    unsigned int search_time2 = end_time - start_time;

    cout << "first element find in " << search_time1 << "ms" << endl;
    cout << "last element find in " << search_time2 << "ms" << endl;
}

int testHeshT(const std::string &BIN_FILE_NAME, const std::string &FILE_NAME) {
    HashTable table(10);
    tableNode *node;
    groupElement *elem;

    int num;
    while (true) {
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
        cout << " 12. Print BIN file" << endl;
        cout << " 13. Insert in hashTable and BIN" << endl;
        cout << " 14. Get hash" << endl;
        cout << " 15. Test with 1000000 records" << endl;
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
                if (tableLength <= 0) {
                    tableLength = 10;
                }
                table = HashTable(tableLength);
                break;
            case 4:
                fillTableFromBin(table, BIN_FILE_NAME);
                break;
            case 5:
                table.print();
                break;
            case 6:
                cout << "write groupId, medianScore, studentCount, predmetId" << endl;
                int groupId1;
                double medianScore;
                int studentCount;
                int predmetId;
                cin >> groupId1 >> medianScore >> studentCount >> predmetId;
                elem = new groupElement(groupId1, medianScore, studentCount, predmetId);
                table.insert(*elem);
                cout << "insert with index " << hashIndex(groupId1, table.length) << endl;
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
                *elem = findInBinByKey(table, groupId5, BIN_FILE_NAME);
                cout << elem->groupId << endl;
                break;
            case 12:
                printOutBinFile(BIN_FILE_NAME);
                break;
            case 13:
                addEntry(table, BIN_FILE_NAME);
                break;
            case 14:
                cout << "write groupId" << endl;
                int groupId6;
                cin >> groupId6;
                cout << hashIndex(groupId6, table.length) << endl;
                break;
            case 15:
                cout << "Test with many records" << endl;
                milTest(table, BIN_FILE_NAME);
                break;
            case 0:
                exit(0);
            default:
                cout << "unknown number. write 0 to exit." << endl;
                break;
        }
    }
}

