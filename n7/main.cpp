//
// Created by 0ilya on 07.12.2022.
//

#include <iostream>
#include <vector>
#include <iomanip>
#include <chrono>

using namespace std;

bool isZeroBlock(vector<vector<int>> matrix, int x0, int y0, int size);

int findMaxZeroBlock(vector<vector<int>> matrix, int x, int y, int size);

void fillMatrix(vector<vector<int>> &arr, int M, int N);

void printMatrix(vector<vector<int>> arr, int M, int N);

int main() {
    int M = 30; //rows - y
    int N = 30; //cols - x
    int maxSize = 1;
    int maxX = 0;
    int maxY = 0;
    int pereborCount = 0;
    /*cout << "Enter matrix size(M): ";
    cin >> M;
    cout << "Enter matrix size(N): ";
    cin >> N;*/

    vector<vector<int>> arr(M, vector<int>(N));

    fillMatrix(arr, M, N);

    printMatrix(arr, M, N);

    //findMaxZeroBlock
    auto start = std::chrono::high_resolution_clock::now();
    for (int y = 0; y < arr.size()-1; y++)
        for (int x = 0; x < arr[0].size()-1; x++)
            if (arr[y][x] == 0 && arr[y + 1][x] == 0 && arr[y][x + 1] == 0 && arr[y + 1][x + 1] == 0) {
                int curMax = findMaxZeroBlock(arr, x, y, maxSize);
                if (curMax > maxSize) {
                    maxSize = curMax;
                    maxX = x + 1;
                    maxY = y + 1;
                }
                pereborCount++;
            }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    cout << "Max size: " << maxSize << endl;
    cout << "Coordinates: (" << maxX << "; " << maxY << ")" << endl;
    cout << "Branch and bound time: " << elapsed.count() << "s" << endl;
    cout << "Branch and bound count: " << pereborCount << endl;

    pereborCount = 0;
    auto start2 = std::chrono::high_resolution_clock::now();
    for (int y = 0; y < arr.size(); y++)
        for (int x = 0; x < arr[0].size(); x++) {
            findMaxZeroBlock(arr, x, y, 0);
            pereborCount++;
        }

    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed2 = end2 - start2;
    cout << "Classic time: " << elapsed2.count() << "s" << endl;
    cout << "Classic count: " << pereborCount << endl;
    return 0;
}

bool isZeroBlock(vector<vector<int>> matrix, int x0, int y0, int size) {
    for (int y = y0; y < y0 + size; y++) {
        for (int x = x0; x < x0 + size; x++) {
            if (matrix[y][x] != 0) return false;
        }
    }
    return true;
}

int findMaxZeroBlock(vector<vector<int>> matrix, int x, int y, int size) {
    if (y + size > matrix.size() || x + size > matrix[0].size() || !isZeroBlock(matrix, x, y, size)) {
        return size - 1; // Return the maximum size of the zero block found so far
    }
    return findMaxZeroBlock(matrix, x, y, size + 1); // Continue expanding the block in all four directions
}

void fillMatrix(vector<vector<int>> &arr, int M, int N) {
    int manual = 0;
    //cout << "Enter 1 to enter matrix manually, 0 to generate random matrix or -1 to generate matrix with 1: ";
    //cin >> manual;
    int T = 4; //required max size of zero block
    if (manual == 1) {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                cin >> arr[i][j];
            }
        }
    } else if (manual == 0) {
        bool flag = true;
        while (flag) {
            srand(time(NULL));
            for (int y = 0; y < M; y++)
                for (int x = 0; x < N; x++)
                    arr.at(y).at(x) = (rand() % 2); //fill matrix with random values

            //check if there is a square with size T filled with 0
            for (int y = 0; flag && y < M - T; y++)
                for (int x = 0; flag && x < N - T; x++)
                    if (isZeroBlock(arr, x, y, T)) {
                        cout << "While creating a matrix found a square with size " << T << " filled with 0" << endl;
                        cout << "Coordinates: " << "(" << x + 1 << "; " << y + 1 << ")" << endl;
                        flag = false;
                    }
        }
    } else {
        for (int y = 0; y < M; y++)
            for (int x = 0; x < N; x++)
                arr.at(y).at(x) = 1; //fill matrix with random values

        //get random coordinates
        srand(time(NULL));
        int ry = rand() % (M - T);
        srand(time(NULL));
        int rx = rand() % (N - T);
        //fill a square with size T with 0
        for (int y = ry; y < ry + T; y++)
            for (int x = rx; x < rx + T; x++)
                arr.at(y).at(x) = 0;

        cout << "Create a square with size " << T << " filled with 0" << endl;
        cout << "Coordinates: " << "(" << rx + 1 << "; " << ry + 1 << ")" << endl;
    }
}

void printMatrix(vector<vector<int>> arr, int M, int N) {
    cout << endl << "x -> ";
    for (int x = 1; x <= N; x++) {
        cout << (x >= 10 ? x % 10 : x) << " ";
    }
    cout << endl;
    for (int y = 0; y < M; y++) {
        cout << std::left << "y" << std::setw(2) << y + 1 << ": "; //print row index
        for (int x = 0; x < N; x++) {
            cout << arr.at(y).at(x) << " ";
        }
        cout << endl;
    }
}