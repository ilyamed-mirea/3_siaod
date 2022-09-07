//
// Created by Илья on 17.05.2022.
//

#include <ctime>
#include <iostream>
#include <queue>
using namespace std;


#define N 8
#define M 8
#define MAXINT 32767

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


using namespace std;

int* Sort(int *A, int size){
    int *tree = new int[size*2];
    int i;

    int k,j=0;

    while ( j < N ){
        tree[size+j] = A[j];
        ++j;
    }

    j = size;
    while (j < 2*size)
    {
        if ( tree[j]>=tree[j+1] )  tree[j / 2] = j;
        else  tree[j / 2] = j + 1;
        j += 2;
    }

    k = size / 2;
    while ( k>=1 )
    {
        j = k;
        while  (j<2*k)
        {
            if ( tree[tree[j]] >= tree[tree[j+1]] )
                tree[j / 2] = tree[j];
            else  tree[j / 2] = tree[j+1];
            j += 2;
        }
        k /= 2;
    }

    for(k=N; k>=2; --k)
    {
        i       = tree[1];
        A[k-1]    = tree[i];
        tree[i] = -MAXINT;


        if  (i % 2)  tree[i / 2] = i - 1;
        else  tree[i / 2] = i + 1;

        i /= 2;

        while  (i>1)
        {
            if  (i % 2)  j = i - 1;
            else  j = i + 1;
            if  (tree[tree[i]]>tree[tree[j]])  tree[i / 2] = tree[i];
            else  tree[i / 2] = tree[j];
            i /= 2;
        }
    }
    A[0] = tree[tree[1]];
    return A;
}

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
