//
// Created by ilyaMedvedev on 01.12.2022.
//

#include "RBSTOperator.h"

using namespace std;

//tree - дерево, в которое будем добавлять элементы
//binFileName - имя файла, из которого будем считывать элементы
void fillTreeFromBin(RBSTTRee &tree, std::string binFileName) {
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

//tree - дерево, в котором будем удалять элемент
//binFileName - имя файла, в котором будем удалять элемент
//groupId - ключ, по которому будем удалять элемент
void removeEntry(RBSTTRee &tree, const std::string &binFileName, int groupId) {
    //int key = tree.find(groupId)->data;
    tree.remove(groupId);
    int newDeletedData = deleteEntryByKey(groupId, binFileName);
    RBSTNode* last = tree.findLast(tree.head, tree.head);
    last->data = newDeletedData;
}

//tree - дерево, в котором будем искать элемент
//binFileName - имя файла, в котором будем искать элемент
//groupId - ключ, по которому будем искать элемент
groupElement findInBinByKey(RBSTTRee &tree, int groupId, const std::string &binFileName) {
    RBSTNode* foundInTree = tree.find(groupId);
    int order;
    if (!foundInTree) {
        cout << "No such element" << endl;
        return groupElement();
    }
    else order=foundInTree->data;
    return getEntryFromBin(binFileName, order);
}

//tree - дерево, в которое будем добавлять элемент
//binFileName - имя файла, в который будем добавлять элемент
//element - элемент, который будем добавлять
void addEntry(RBSTTRee &tree, const std::string &binFileName, groupElement element) {
    tree.insert(element.groupId, getFileLength(binFileName));
    addEntryInBin(binFileName, element);
}

int countRotating() {
    RBSTTRee tree;
    srand(time(nullptr));
    int counter = 0;
    for (int i=0;i<100;i++)
        tree.insert((int)rand()*100, i);
    counter += tree.rotatingCount;

    tree = *new RBSTTRee();
    for (int i=0;i<100;i++)
        tree.insert((int)rand()*100, i);
    counter += tree.rotatingCount;

    tree = *new RBSTTRee();
    for (int i=0;i<100;i++)
        tree.insert((int)rand()*100, i);
    counter += tree.rotatingCount;

    tree = *new RBSTTRee();
    for (int i=0;i<100;i++)
        tree.insert((int)rand()*100, i);
    counter += tree.rotatingCount;

    return counter/4;
}
