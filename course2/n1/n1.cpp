#include <iostream>
#include <string>
using namespace std;
const int length = 100;

void getArr(int* arr, int length) {
    cout << "������� �������� �������" << endl;
    for (int i = 0; i < length; i++) {
        int a;
        while (true) {
            cin >> a;
            if (cin.fail() || cin.peek() != '\n') {
                cin.clear();
                cin.ignore(32777, '\n');
                cout << "Input error! Repeat please..." << endl;
            }
            else
                break;
        }
        arr[i] = a;
    }
}

void printArr(int* arr, int length) {
    for (int i = 0; i < length; i++) {
        cout << arr[i] << endl;
    }
}

int main() {

    system("chcp 65001");
    cout << "тест?" << endl;
    int a;
    cin >> a;
    return 0;
}