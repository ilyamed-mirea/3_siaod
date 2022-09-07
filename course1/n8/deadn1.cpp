//
// Created by Илья on 17.05.2022.
//

#include <ctime>
#include <iostream>
using namespace std;

int *getRandomArr(int size) {
    int *arr = new int[size];
    srand(time(NULL));

    for (int i = 0; i < size; i++)
        arr[i] = rand() % 100;

    return arr;
}

int *getArr(int size) {
    int *arr = new int[size];

    for (int i = 0; i < size; i++)
        cin >> arr[i];

    return arr;
}
void simpleChoiceSort(int *arr, int size) {
    int init = -100;
    for (int i = 0; i < size-1; i++) {
        int *max = &init;
        for (int j = i; j < size; j++)
            if (arr[j] > (*max)) {
                max = &arr[j];
            }
        swap(arr[i],*max);
    }
}
/*
void simpleChoiceSort(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i; j>0 && arr[j-1]>arr[j]; j--)
            swap(arr[j-1],arr[j]);
    }
}
*/
void printArr(int *arr, int size) {
    for (int i=0;i<size;i++)
        cout << *arr++ << " ";
    cout << endl;
}

int main() {
    system("chcp 65001");
    cout << "сортировка методом простого выбора" << endl;
    int size = 0;
    cout << "Введите размер: ";
    cin >> size;

    int *arr = getRandomArr(size);
    printArr(arr,size);

    simpleChoiceSort(arr,size);

    cout << "Output: " << endl;
    printArr(arr,size);
    delete[] arr;
    return 0;
}
