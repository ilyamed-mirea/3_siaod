//
// Created by ilyaMedvedev on 29.11.2022.
//

#include "BinaryTreeOperator.cpp"
#include "iostream"

using namespace std;

const string FILE_NAME = "tree.txt";
const string BIN_FILE_NAME = "bin_tree.bin";

int main() {
    Tree tree;

    createTxtFile(FILE_NAME);
    createBinFromTxt(FILE_NAME, BIN_FILE_NAME);
    //printOutBinFile(BIN_FILE_NAME);
    fillTreeFromBin(tree, BIN_FILE_NAME);

    cout<<"Tree:"<<endl;
    tree.printTree();

    cout<<"Tree after removing 300:"<<endl;
    removeEntry(tree, BIN_FILE_NAME, 300);
    tree.printTree();

    cout<<"Tree after adding 25:"<<endl;
    addEntry(tree, BIN_FILE_NAME, 25);
    tree.printTree();

    cout<<"Searching for 1232:"<<endl;
    groupElement found = findInBinByKey(tree, 1232, BIN_FILE_NAME);
    cout << "found " << found.groupId << ": " << found.studentCount << " " << found.medianScore << endl;

    return 0;
}