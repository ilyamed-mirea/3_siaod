//
// Created by ilyaMedvedev on 01.12.2022.
//

#include "RBSTOperator.h"

using namespace std;

void fillTreeFromBin(Tree &tree, std::string binFileName) {
    int binFileLength = getFileLength(binFileName);
    ifstream binFile(binFileName);
    openFile(binFile, binFileName, "in");
    groupElement element;
    for (int i = 0; i < binFileLength; i++) {
        binFile.read((char *) &element, sizeof(groupElement));
        tree.insert(element.groupId, i);
    }
    binFile.close();
}

void removeEntry(Tree &tree, const std::string &binFileName, int groupId) {
    //int key = tree.find(groupId)->data;
    tree.remove(groupId);
    int newDeletedData = deleteEntryByKey(groupId, binFileName);
    Node* last = tree.findLast(tree.head, tree.head);
    last->data = newDeletedData;
}

//void findInTree(Tree &tree, std::string binFileName);

groupElement findInBinByKey(Tree &tree, int groupId, const std::string &binFileName) {
    Node* foundInTree = tree.find(groupId);
    int order;
    if (!foundInTree) {
        cout << "No such element" << endl;
        return groupElement();
    }
    else order=foundInTree->data;
    return getEntryFromBin(binFileName, order);
}

void addEntry(Tree &tree, const std::string &binFileName, groupElement element) {
    tree.insert(element.groupId, getFileLength(binFileName));
    addEntryInBin(binFileName, element);
}
