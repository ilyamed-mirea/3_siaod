//
// Created by 0ilya on 07.12.2022.
//

#include <iostream>
using namespace std;
#include <cstdlib>

int main() {
    int M = 4, N = 4;
    //cin >> M >> N;
    int block[M][N];
    bool flag = true;
    while (flag) {
        srand(time(NULL));
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                block[i][j] = rand() % 2;
            }
        }
        for (int i = 0; i < M - 1; i++) {
            for (int j = 0; j < N - 1; j++) {
                if (block[i][j] == 0 && block[i][j + 1] == 0 && block[i + 1][j] == 0 && block[i + 1][j + 1] == 0) {
                    flag = false;
                    break;
                }
            }
        }
    }
cout << endl;
    //print block
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            cout << block[i][j] << " ";
        }
        cout << endl;
    }



    return 0;
}