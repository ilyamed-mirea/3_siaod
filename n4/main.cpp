//
// Created by ilyaMedvedev on 29.11.2022.
//

#include "Tree.cpp"
#include "iostream"

using namespace std;

int main() {
    Tree tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);
    tree.insert(1);
    tree.insert(9);
    tree.insert(10);

    /*tree.insert(11);
    tree.insert(22);
    tree.insert(10);
    tree.insert(2);
    tree.insert(6);
    tree.insert(1);
    tree.printTree("", tree.head, false);

    tree.remove(2);*/

    tree.printTree("", tree.head, false);

    cout << "sum: " << tree.findSum(tree.head) << endl; //55

    cout << "leaves: " << tree.countLeaves(tree.head) << endl; //4

    tree.removeMax();

    tree.printTree("", tree.head, false);

    tree.remove(7, tree.head);

    tree.printTree("", tree.head, false);

    Node *found = tree.find(6);
    cout << "found 6: " << found->data << endl;

    return 0;
}