//
// Created by ilyaMedvedev on 29.11.2022.
//

#include "Tree.cpp"
#include "iostream"

using namespace std;

int main() {
    return;
    Tree tree;
    /*tree.insert(5, tree.head);
    tree.insert(3, tree.head);
    tree.insert(7, tree.head);
    tree.insert(2, tree.head);
    tree.insert(4,  tree.head);
    tree.insert(6, tree.head);
    tree.insert(8, tree.head);
    tree.insert(1, tree.head);
    tree.insert(9, tree.head);
    tree.insert(10, tree.head);*/

    tree.insert(12, tree.head);
    tree.insert(10, tree.head);
    tree.insert(25, tree.head);
    tree.insert(8, tree.head);
    tree.insert(5, tree.head);
    tree.insert(22, tree.head);
    tree.insert(28, tree.head);
    tree.insert(14, tree.head);
    tree.insert(44, tree.head);
    tree.printTree("", tree.head, false);

    tree.remove(2, tree.head);

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