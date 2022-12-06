//
// Created by ilyaMedvedev on 02.12.2022.
//

#include <random>
#include <chrono>

#include "../../n3/hashTable.cpp"
#include "../n1/Tree.cpp"
#include "RBST.cpp"
#include "../../base/groupElement.cpp"

double checkHashSpeed(int *array, int key, int i);

double checkBinaryTreeSpeed(int *array, int key, int i);

double checkRBSTSpeed(int *array, int key, int i);

int checkSPeed() {
    int maxNumber = 1000000;
    int *array = new int[maxNumber];
    for (int i = 0; i < maxNumber; i++) {
        array[i] = i;
    }
    random_shuffle(&array[0], &array[maxNumber]);

    for (int i = 10; i <= maxNumber; i *= 10) {
        double hashSpeed = 0;
        double binaryTreeSpeed = 0;
        double rbstSpeed = 0;
        for (int k = 0; k < 4; k++) {
            int *currentArray = new int[i];
            for (int j = 0; j < i; j++) {
                currentArray[j] = array[j];
            }
            srand(time(nullptr));
            int key = currentArray[rand() % i];
            hashSpeed += checkHashSpeed(currentArray, key, i);
            binaryTreeSpeed += checkBinaryTreeSpeed(currentArray, key, i);
            rbstSpeed += checkRBSTSpeed(currentArray, key, i);
        }
        cout << i << " elements:" << endl;
        cout << "Search in hash: " << (int) hashSpeed / 4 << " ns" << endl;
        cout << "Search in binary tree: " << (int) binaryTreeSpeed / 4 << " ns" << endl;
        cout << "Search in RB tree: " << (int) rbstSpeed / 4 << " ns" << endl;

        cout << endl;
    }
    return 0;
}

double checkRBSTSpeed(int *array, int key, int i) {
    RBSTTRee tree;
    for (int j = 0; j < i; j++) {
        tree.insert(array[j], array[j]);
    }
    auto start = std::chrono::high_resolution_clock::now();
    RBSTNode *found = tree.find(key);
    auto end = std::chrono::high_resolution_clock::now();
    return chrono::duration<double, nano>(end - start).count();
}

double checkBinaryTreeSpeed(int *array, int key, int i) {
    Tree tree;
    for (int j = 0; j < i; j++) {
        tree.insert(array[j], j);
    }
    auto start = std::chrono::high_resolution_clock::now();
    Node *found = tree.find(key);
    auto end = std::chrono::high_resolution_clock::now();
    return chrono::duration<double, nano>(end - start).count();
}

double checkHashSpeed(int *array, int key, int i) {
    HashTable hashTable(i);
    for (int j = 0; j < i; j++) {
        groupElement element(array[j]);
        hashTable.insert(element, j);
    }
    auto start = std::chrono::high_resolution_clock::now();
    tableNode *found = hashTable.search(key, -1);
    auto end = std::chrono::high_resolution_clock::now();
    return chrono::duration<double, nano>(end - start).count();
}


int main() {
    checkSPeed();
    return 0;
}