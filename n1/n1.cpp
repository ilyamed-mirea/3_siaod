#include <iostream>
#include <string>
using namespace std;

void bonus() {
    //     p
    // 101110 = 46
    // res 000010 = 2
    // p = 1;
    int x,p;
    cin >> x >> p;
    unsigned int mask = ~0 << (p + 1);
    x = x & (~mask);
    cout << x << endl;
}

void n1() {
    unsigned int mask = 0x86;
    unsigned int x = 0x1A1;
    int res = x | mask;
    cout << res << endl;
}

void n2() {
    unsigned int mask = 0xFF;
    unsigned int x;
    cin >> x;
    //cout << (x & ~((1 << 7) | (1 << 8) | (1 << 9)));
    x = x & mask;
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
    cout << x << endl;
}

int main() {

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

