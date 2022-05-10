#include <iostream>
#include <string>

using namespace std;

int findMax(int num, int curMax) {
    string numStr = to_string(num);
    int len = int(numStr.length()) - 1;
    if (num>0)
        curMax = findMax(num/10, int(numStr[len]-'0') > curMax ? int(numStr[len]-'0') : curMax);
    return curMax;
}

int main() {
    system("chcp 65001");

    cout << "Введите число: " << endl;
    int gotNum;
    cin >> gotNum;
    cout << "Наибольшая цифра:" << endl;
    int maxNum = findMax(gotNum, 0);
    cout << maxNum << endl;

    system("pause");

    return 0;
};