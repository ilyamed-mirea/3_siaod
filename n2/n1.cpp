#include <iostream>
#include <ctime>
using namespace std;
const int MAXROWS = 100;
const int MAXCOLS = 100;

void getFromKeyboard(int matrix[][MAXCOLS], int diag) {
    for (int i = 0; i < diag; i++) {
        for (int j = 0; j < diag; j++) {
            cout << "write [" << i << "][" << j << "] element:";
            cin >> matrix[i][j];
        }
    }
}

void getByRandom(int matrix[][MAXCOLS], int diag) {
    srand(time(NULL));
    for (int i = 0; i < diag; i++) {
        for (int j = 0; j < diag; j++) {
            matrix[i][j] = rand()%100;
        }
    }
    cout << "matrix fullfilled by random" << endl;
}

void print(int matrix[][MAXCOLS], int diag) {
    for (int i = 0; i < diag; i++) {
        for (int j = 0; j < diag; j++) {
            cout << "element [" << i << "][" << j << "]: " << matrix[i][j] << endl;
        }
    }
}

void findRes(int matrix[][MAXCOLS], int diag, int &res) {

}

int main()
{
    system("chcp 65001");
    int matrix[MAXCOLS][MAXROWS] = {0};
    int diag = 0;
    cout << "write diag colv" << endl;
    while (cin >> diag) {
        if (diag > 0 && diag < MAXROWS && diag < MAXROWS) break;
        else cout << "error. wrong number. try again" << endl;
    };
    int* res = new int[diag];
    //getFromKeyboard(matrix, diag);
    getByRandom(matrix, diag);
    print(matrix, diag);
    //findRes(matrix, diag, res);
}