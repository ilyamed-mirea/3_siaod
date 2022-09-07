#include <iostream>
#include <string>
using namespace std;

int findIndex(int* arr, int length) {
    for (int i = 0; i < length; i++) {
        int colv1 = 0;
        int cur10 = arr[i];
        int cur2 = 0;
        int d = 1;
        while (cur10) {
            cur2 += cur10 % 2 * d;
            cur10 /= 2;
            d *= 10;
        }
        while (cur2) {
            if (cur2 % 10 == 1) {
                colv1++;
            }
            cur2 /= 10;
        }
        if (colv1 == 3) {
            return i;
        }
    }
    return -1; //error flag
}

void insertAfter(int*& arr, int& length, int num, int index) {
    int newlen = length + 1;
    int* arr2 = new int[newlen];
    memcpy(arr2, arr, length * sizeof(int));
    index++;
    for (int i = newlen; i > index; i--) {
        arr2[i] = arr2[i - 1];
    }
    arr2[index] = num;
    delete[] arr;
    arr = arr2;
    length = newlen;
}

void deleteElement(int*& arr, int& n, int index) {
    n--;
    int* arr2 = new int[n];
    int razn = 0;
    for (int i = 0; i < n+1; i++) {
        if (i != index) {
            arr2[i-razn] = arr[i];
        }
        else {
            razn++;
        }
    }
    delete[] arr;
    arr = arr2;
}

void getArr(int* arr, int length) {
    cout << "Вводите элементы массива" << endl;
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
    int n = -1;
    int chooser = 100;
    int* arr = 0;
    int index = -1;

    while (chooser != 0) {
        system("cls");

        cout << "Лабораторная работа №1 ИНБО-08-21 Медведев И.В. Вариант 16" << endl << endl;
        cout << "Задание 2" << endl;
        cout << "Меню\n";
        cout << "1) Заполнить массив\n";
        cout << "2) Вывести массив\n";
        cout << "3) Найти индекс первого элемента, у которого двоичный код содержит ровно 3 единицы\n";
        cout << "4) Вставить новый элемент в массив после заданного индекса\n";
        cout << "5) Удалить все элементы, у которых в двоичном коде ровно 3 единицы\n";
        cout << "0) Выход\n";

        cout << "Ваш выбор: ";
        cin >> chooser;

        switch (chooser)
        {
            case 1: {
                cout << "Введите кол-во элементов в массиве: ";
                while (cin >> n) {
                    if (n <= 0) {
                        cout << "Слишком  маленькое значение. попробуйте еще раз" << endl;
                    }
                    else break;
                }
                arr = new int[n];
                getArr(arr, n);
                system("pause");
                break;
            }
            case 2: {
                if (n == -1) {
                    cout << "Массив не задан. Попробуйте еще раз." << endl;
                    system("pause");
                    break;
                }
                cout << "Вывод массива" << endl;
                printArr(arr, n);
                system("pause");
                break;
            }
            case 3: {
                index = findIndex(arr, n);
                if (index == -1) {
                    cout << "ошибка. элемент не найден." << endl;
                }
                else cout << "Индекс: " << index << endl;
                system("pause");
                break;
            }
            case 4: {
                if (n == -1) {
                    cout << "Массив не задан. Попробуйте еще раз." << endl;
                    system("pause");
                    break;
                }
                if (index == -1) {
                    cout << "Внимание! Индекс элемента, после которого надо вставить новый, не задан! Напишите 1 если хотите выйти в меню или 0 если хотите ввести индекс самостоятельно" << endl;
                    int ans;
                    cin >> ans;
                    if (ans == 0) {
                        cout << "Введите индекс" << endl;
                        cin >> index;
                    }
                    else break;
                }
                cout << "Введите число, которое хотите вставить" << endl;
                int num;
                cin >> num;
                cout << "Массив со вставленным элементом" << endl;
                insertAfter(arr, n, num, index);
                printArr(arr, n);
                system("pause");
                break;
            }

            case 5: {
                if (n == -1) {
                    cout << "Массив не задан. Попробуйте еще раз." << endl;
                    system("pause");
                    break;
                }
                cout << "Массив после удаления элементов, двоичный код которых содержит ровно 3 единицы:" << endl;
                int found = findIndex(arr, n);
                while (found != -1) {
                    deleteElement(arr, n, found);
                    found = findIndex(arr, n);
                }

                printArr(arr, n);
                system("pause");
                break;
            }

            case 0: {
                return 0;
            }
            default: {
                chooser = 100;
                break;
            }

        }

    }
    return 0;
}