#include <iostream>
#include <string>
#include <vector>
using namespace std;

int findIndex(vector <int> &arr) {
    for (int i = 0; i < arr.size(); i++) {
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

void insertAfter(vector <int>& arr, int num, int index) {
    auto iter = arr.cbegin();
    arr.insert(iter+index+1, num);
}

void deleteElement(vector <int>& arr, int index) {
    auto iter = arr.cbegin();
    arr.erase(iter+index);
}

void getArr(vector <int>& arr, int n) {
    cout << "Вводите элементы массива" << endl;
    for (int i = 0; i < n; i++) {
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
        arr.push_back(a);
    }
}

void printArr(vector <int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr.at(i) << endl;
    }
}

int main() {

    system("chcp 65001");
    int n = -1;
    int chooser = 100;
    vector<int> arr;
    int index = -1;

    while (chooser != 0) {
        system("cls");

        cout << "Лабораторная работа №1 ИНБО-08-21 Медведев И.В. Вариант 16" << endl << endl;
        cout << "Задание 3" << endl;
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
                        cout << "число должно быть больше нуля" << endl;
                    }
                    else break;
                }
                arr.reserve(n);
                getArr(arr, n);
                system("pause");
                break;
            }
            case 2: {
                if (arr.empty()) {
                    cout << "Массив не задан. Попробуйте еще раз." << endl;
                    system("pause");
                    break;
                }
                cout << "Вывод массива" << endl;
                printArr(arr);
                system("pause");
                break;
            }
            case 3: {
                index = findIndex(arr);
                if (index == -1) {
                    cout << "ошибка. элемент не найден." << endl;
                }
                else cout << "Индекс: " << index << endl;
                system("pause");
                break;
            }
            case 4: {
                if (arr.empty()) {
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
                insertAfter(arr, num, index);
                n++;
                printArr(arr);
                system("pause");
                break;
            }

            case 5: {
                if (arr.empty()) {
                    cout << "Массив не задан. Попробуйте еще раз." << endl;
                    system("pause");
                    break;
                }
                cout << "Массив после удаления элементов, двоичный код которых содержит ровно 3 единицы:" << endl;
                int found = findIndex(arr);
                while (found != -1) {
                    deleteElement(arr, found);
                    n--;
                    found = findIndex(arr);
                }

                printArr(arr);
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