//
// Created by ilyaMedvedev on 29.11.2022.
//

#include "RBSTOperator.cpp"
#include "iostream"

using namespace std;

const string FILE_NAME = "tree.txt";
const string BIN_FILE_NAME = "bin_tree.bin";

int main() {
    Tree tree;

    createTxtFile(FILE_NAME);
    createBinFromTxt(FILE_NAME, BIN_FILE_NAME);
//    printOutBinFile(BIN_FILE_NAME);
    fillTreeFromBin(tree, BIN_FILE_NAME);

    cout << "Tree:" << endl;
    tree.printTree();

    cout << "Tree after removing 56:" << endl;
    removeEntry(tree, BIN_FILE_NAME, 56);
    tree.printTree();

    cout << "Tree after adding 413:" << endl;
    addEntry(tree, BIN_FILE_NAME, 413);
    tree.printTree();

    int searchKey = 4;
    //cin >> searchKey;
    cout << "Searching for: " << searchKey << endl;
    groupElement found = findInBinByKey(tree, searchKey, BIN_FILE_NAME);
    if (found.studentCount != -1 && found.medianScore != -1)
        cout << "found " << found.groupId << ": " << found.studentCount << " " << found.medianScore << endl;

    cout << "rotating count: " << tree.rotatingCount << endl;

    return 0;
}