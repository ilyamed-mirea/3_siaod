#include <iostream>
#include <string>
using namespace std;

#define SIZE (8999999 / 32 + 1)
 
void getArr(int* arr) {
    unsigned int len; 
    cout << "write arr length" << endl;
    while (cin >> len) {
        if (len > 0) break;
        else cout << "too low. try again" << endl;
    };
    for (int i = 0; i < len; i++) {
        while (true) {
            int num;
            cout << endl << "write arr[" << i << "]:" << endl;
            cin >> num;
            if (num > 9999999 || num < 1000000) {
                cout << "number must have 7 digits. try again" << endl;
                continue;
            }
            num -= 1000000; //optimisation 
            unsigned int bits = 1 << (32 - (num % 32) - 1);
            arr[num / 32] |= bits;
            break;
        }
    }
}

void printArr(int* arr) {
    cout << "result:" << endl;
    for (int posinArr=0; posinArr<SIZE; posinArr++) {
        unsigned mask = (1 << (32 - 1));
        for (int i = 0; i < 32; i++) {
            if ((arr[posinArr] & mask) >> (32 - 1 - i) == 1)
                cout << i + posinArr*32 + 1000000 << endl;
            mask = mask >> 1;
        }
    }
}

int mainX() {
    system("chcp 65001");

    int* arr = new int[SIZE] {0};
    
    getArr(arr);
    printArr(arr);
    cout << endl <<"write num to exit" << endl;
    int pause;
    cin >> pause;

    return 0;
}