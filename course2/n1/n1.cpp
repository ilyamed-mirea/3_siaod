#include <iostream>
#include <string>
using namespace std;

void n1() {
    unsigned int mask = 0x86; //134 в 10
    unsigned int x = 0x1A1; //1 в 10
    int res = x | mask; //135 в 10
    cout << res << endl;
}

void n2() {
    unsigned int mask = 0xFF;
    unsigned int x;
    cin >> x;
    x = x & mask;
    //x = x & ~((mask << 7) | (mask << 8) | (mask << 9));
    cout << x << endl; //int
    printf("%#010x", x); //16x sys
}

void n3() {
    unsigned int x;
    cin >> x;
    x = x << 3; //*2^n
    cout << x << endl; 
}

void n4() {
    unsigned int x;
    cin >> x;
    x = x >> 3;
    cout << x << endl;
}

void n5() {
    unsigned int x, n;
    cin >> x >> n;
    const unsigned mask = 1;
    x = x & ~(mask << n);
    cout << x << endl; //int
}

int mainX() {

    system("chcp 65001");
    
    unsigned int n,x = 0x0;
    cout << "n1" << endl;
    n1();

    cout << endl << "n2" << endl << "Введите  x" << endl;
    n2();

    cout << endl << "n3" << endl << "Введите  x" << endl;
    n3();

    cout << endl << "n4" << endl << "Введите  x" << endl;
    n4();

    cout << endl << "n5" << endl << "Введите  x,n" << endl;
    n5();

    cout << endl << "Введите число для выхода" << endl;
    cin >> x;
    
    return 0;
}

