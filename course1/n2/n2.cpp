#include <iostream>
#include <ctime>
using namespace std;

// заполнение с клавиатуры
void getFromKeyboard(int **matrix, int diag) {
    for (int i = 0; i < diag; i++) {
        for (int j = 0; j < diag; j++) {
            int a;
            while (true) {
                cout << "write [" << i << "][" << j << "] element: ";
                cin >> a;
                if (cin.fail() || cin.peek() != '\n') {
                    cin.clear();
                    cin.ignore(32777, '\n');
                    cout << "Ошибка ввода. Пожалуйста, повторите..." << endl;
                }
                else {
                    matrix[i][j] = a;
                    break;
                }
            }
        }
    }
    cout << "Матрица заполнена" << endl;
}

// заполнение матрицы случайными значениями
void getByRandom(int **matrix, int diag) {
    srand(time(NULL));
    for (int i = 0; i < diag; i++) {
        for (int j = 0; j < diag; j++) {
            matrix[i][j] = rand() % 100;
        }
    }
    cout << "Матрица заполнена случайными числами" << endl;
}

// вывод матрицы
void print(int **matrix, int diag) {
    for (int i = 0; i < diag; i++) {
        for (int j = 0; j < diag; j++) {
            cout << "element [" << i << "][" << j << "]: " << matrix[i][j] << endl;
        }
    }
}

// заполнение массивов диагоналей
void generateArrays(int **matrix, int diag, int *&arrMain, int *&arrDop) {
    for (int i = 0; i < diag; i++) {
        arrMain[i] = matrix[i][i];
        arrDop[i] = matrix[i][diag - i - 1];
    }
}

// заполнение и возврат массива произведений элементов диагоналей
int *mergeArrays(int *&arrMain, int *&arrDop, int diag) {
    int *cur = new int[diag];
    for (int i = 0; i < diag; i++) {
        cur[i] = arrMain[i] * arrDop[i];
    }
    return cur;
}

// вывод одномерного массива с результатами
void printRes(int *&arr, int diag) {
    for (int i = 0; i < diag; i++) {
        cout << "[" << i << "]: " << arr[i] << endl;
    }
}

int main() {
    system("chcp 65001");
    int **matrix;
    int diag = 0;
    int chooser = 100;
    int *res;

    while (chooser != 0) {
        system("cls");

        cout << "Лабораторная работа №2 ИНБО-08-21 Медведев И.В. Вариант 16" << endl << endl;
        cout << "Задание 2" << endl;
        cout << "Меню\n";
        cout << "1) Заполнить матрицу\n";
        cout << "2) Вывести матрицу на экран\n";
        cout << "3) Сформировать одномерный массив произведений элементов главной и побочной диагонали, имеющих одинаковый индекс строки\n";
        cout << "4) Вывести массив произведений\n";
        cout << "0) Выход\n";

        cout << "Ваш выбор: ";
        cin >> chooser;

        switch (chooser) {
            case 1: {
                cout << "Введите длину диагонали матрицы" << endl;
                while (cin >> diag) {
                    if (diag > 0) break;
                    else cout << "ошибка. неправильное значение. попробуйте еще раз" << endl;
                };
                res = new int[diag];
                matrix = new int* [diag];
                for (int i = 0; i < diag; i++)
                    matrix[i] = new int[diag];
                cout
                        << "Введите 1 если хотите заполнить матрицу с клавиатуры или 0 если хотите заполнить ее случайными числами"
                        << endl;
                int randorkey;
                cin >> randorkey;
                while (randorkey != 0 && randorkey != 1) {
                    cout << "ошибка. неправильное значение. попробуйте еще раз" << endl;
                    cin >> randorkey;
                }
                if (randorkey == 1) getFromKeyboard(matrix, diag);
                else getByRandom(matrix, diag);

                system("pause");
                break;
            }
            case 2: {
                if (diag==0) {
                    cout << "Матрица не задана." << endl;
                    system("pause");
                    break;
                }
                cout << "Вывод матрицы" << endl;
                print(matrix, diag);
                system("pause");
                break;
            }
            case 3: {
                if (diag==0) {
                    cout << "Матрица не задана." << endl;
                    system("pause");
                    break;
                }
                int *arrMain = new int[diag];
                int *arrDop = new int[diag];
                generateArrays(matrix, diag, arrMain, arrDop);
                cout << "массивы из значений главной и побочной диагонали сформированы" << endl;
                res = mergeArrays(arrMain, arrDop, diag);
                cout << "массив произведений элементов с одинаковыми индексами сформирован" << endl;
                system("pause");
                break;
            }
            case 4: {
                if (diag==0) {
                    cout << "Матрица не задана." << endl;
                    system("pause");
                    break;
                }
                printRes(res, diag);
                system("pause");
                break;
            }

            case 0: {
                delete[] res;
                for (int i = 0; i < diag; i++)
                    delete []matrix[i];
                return 0;
            }
            default: {
                chooser = 100;
                break;
            }

        }
    }
}