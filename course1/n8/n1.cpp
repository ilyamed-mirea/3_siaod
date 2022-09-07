#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;

void array_fill(int *arr, int n) {
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
}

void array_filled_backwards(int *arr, int n){
    for (int i = 0; i < n; ++i) {
        arr[i] = n-i;
    }
}

void sorted_fill(int *arr, int n){
    for (int i = 0; i < n; ++i) {
        arr[i] = i;
    }
}

void random_array(int *arr, int n) {
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % 100;
    }
}

void print(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        cout << setw(4) << arr[i];
    }
    cout << endl;
}

void bubbleSort(int *arr, int n) { // n - длина массива
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) { // проход по массиву
            if (arr[j] > arr[j + 1]) //если текущий больше следующего
                swap(arr[j], arr[j + 1]); // поменять элементы массива местами
        }
    }
}

void countSort(int *arr, int len) {
    int max_num = arr[0];

    for (int i = 1; i < len; i++)
        if (arr[i] > max_num) max_num = arr[i]; // нахождение максимального числа в массиве

    int arr_len = max(max_num, len);

    int *counter = new int[arr_len + 1]; // счётчик количества вхождкний элемента в массиве
    int *sorted_arr = new int[arr_len + 1]; // отсортированный массив

    fill(counter, counter + arr_len + 1, 0); //заполнение массива нулевыми значениями

    for (int i = 0; i < len; i++)
        counter[arr[i]]++; // заполнение счетчика. пример: если в массиве две тройки, counter[3] = 2

    for (int i = 1; i <= arr_len; i++)
        counter[i] += counter[i - 1]; // к каждому следующему элементу счётчика прибавляем предыдущий

    for (int i = len - 1; i >= 0; i--) {
        sorted_arr[counter[arr[i]] - 1] = arr[i]; // установка элемента исходного массива с индексом i в отсортированный массив на место, соответствующее элементу counter по индексу текущего числа - 1
        counter[arr[i]]--; // уменьшение значения счетчика по индексу текущего элемента массива
    }

    for (int i = 0; i < len; i++) { // запись отсортированного массива в исходный
        arr[i] = sorted_arr[i];
    }
}

int partition(int *arr, int low, int high) {
    int pivot = arr[high]; // опорный элемент
    int i = low; // с этого значения начинаем идти по массиву, в i хрнаится индекс массива arr
    for(int j = low; j < high; j++){ // от начала до опорного
        if(arr[j] < pivot){ // если текущий меньше опорного, меняем местаси
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[high]);
    return i; //возврат индекса нового опорного
}

void quickSort(int *arr, int low, int high) {
    if (low >= high) return;

    int i = partition(arr, low, high); //разбить массив на две части - до и после опорного
    quickSort(arr, low, i - 1); // для меньших отрезков
    quickSort(arr, i + 1, high); // для больших
}

int main() {
    system("chcp 65001");

    int choice1 = -1, choice0;

    while (choice1 != 0) {
        cout << "1) заполнить массив вручную" << endl;
        cout << "2) заполнить массив псевдослучайными числами" << endl;
        cout << "3) заполнить массив отсортированными значениями" << endl;
        cout << "4) заполнить массив отсортированными значениями по убыванию" << endl;
        cout << "0) завершить программу" << endl;
        cin >> choice1;
        int len;
        if (choice1==0)
            return 0;
        cout << "введите длину массива: ";
        cin >> len;
        int *arr = new int[len];
        switch (choice1) {
            case 1: // заполнить массив вручную
                cout << "Введите элементы массива: " << endl;
                array_fill(arr, len);
                break;
            case 2: // заполнить массив псевдослучайными числами
                random_array(arr, len);
                //print(arr, len);
                cout << endl;
                break;
            case 3: //заполнить массив отсортированными значениями
                sorted_fill(arr, len);
                cout << endl;
                break;
            case 4: //заполнить массив отсортированными значениями по убыванию
                array_filled_backwards(arr, len);
                cout << endl;
                break;
        }
        print(arr,len);
        cout << "1) Сортировка простым обменом" << endl;
        cout << "2) Сортировка подсчетом" << endl;
        cout << "3) Быстрая сортировка с опорным последним элементом" << endl;
        cin >> choice0;
        switch (choice0) {
            case 1: {
                auto time1 = std::chrono::steady_clock::now();
                bubbleSort(arr, len);
                auto time2 = std::chrono::steady_clock::now();
                std::cout << "Время работы: " << std::chrono::duration<double, milli>(time2 - time1).count();
                cout << endl;
                break;
            }
            case 2: {
                auto time1 = std::chrono::steady_clock::now();
                countSort(arr, len);
                auto time2 = std::chrono::steady_clock::now();
                std::cout << "Время работы: " << std::chrono::duration<double, milli>(time2 - time1).count();
                cout << endl;
                break;
            }
            case 3: {
                auto time1 = std::chrono::steady_clock::now();
                quickSort(arr, 0, len - 1);
                auto time2 = std::chrono::steady_clock::now();
                std::cout << "Время работы: " << std::chrono::duration<double, milli>(time2 - time1).count();
                cout << endl;
                break;
            }
        }
        cout << "Отсортированный массив: " << endl;
        print(arr, len);
    }
    system("pause");
    return 0;
}