//
// Created by 0ilya on 07.12.2022.
//

#include <iostream>
using namespace std;

const int M = 5; //size of array in row
const int N = 7; //size of array in column

//function to find square block of zeros using Branches and Bounds method
void findSquareBlock(int arr[M][N])
{
    bool flag = false; //flag variable to indicate if square block is found
//loop through array
    for(int i=0; i<M; i++)
    {
        for(int j=0; j<N; j++)
        {
//if current element is not zero, continue to next element
            if(arr[i][j] != 0)
                continue;
//if current element is zero, check if next element in same row and next element in same column is also zero
            else if(arr[i][j] == 0 && arr[i][j+1] == 0 && arr[i+1][j] == 0)
            {
                flag = true; //set flag to true
//variables to store coordinates of square block
                int x1 = i;
                int y1 = j;
                int x2 = i;
                int y2 = j+1;
//loop through remaining elements in row and column to find the end coordinates of square block
                for(int k=j+1; k<N; k++)
                {
                    if(arr[i][k] == 0)
                        y2++; //increment y2 coordinate
                    else
                        break;
                }
                for(int k=i+1; k<M; k++)
                {
                    if(arr[k][j] == 0)
                        x2++; //increment x2 coordinate
                    else
                        break;
                }
//print out coordinates of square block
                cout << "Square block found at coordinates: (" << x1 << ", " << y1 << ") to (" << x2 << ", " << y2 << ")" << endl;
                return; //end function
            }
        }
    }
//if flag variable is still false, no square block is found
    if(!flag)
        cout << "No square block consisting of only zeros found" << endl;
}

int main()
{
//initialize 2D array with size M*N
    int arr[M][N] = {{1, 0, 1, 1, 1, 0, 1},
                     {1, 0, 0, 0, 0, 0, 1},
                     {1, 0, 0, 0, 0, 0, 1},
                     {1, 1, 1, 1, 1, 1, 1},
                     {1, 1, 1, 1, 1, 1, 1}};

    findSquareBlock(arr); //call function to find square block of zeros

    return 0;
}

/* V3
#include <iostream>
#include <algorithm>
#include <cmath>

// dimensions of the matrix
const int M = 10;
const int N = 10;
int matrix[M][N];
int maxSize = 0;
int resX = 0;
int resY = 0;

void findZeroSquare(int x, int y, int size) {
    // if the size of the square block is greater than the
    // remaining size of the matrix, we cannot find a square
    // block of zeros
    if (size > std::min(M - x, N - y) || size < 2)
        return;

    // variable to keep track of whether the current square
    // block contains only zeros or not
    bool isZeroSquare = true;

    // loop through the current square block and check if it
    // contains only zeros
    for (int i = x; i < x + size; i++)
        for (int j = y; j < y + size; j++)
            if (matrix[i][j] != 0) {
                isZeroSquare = false;
                break;
            }

    // if the current square block contains only zeros and its
    // size is greater than the maximum size found so far, update
    // the maximum size and the coordinates of the square block
    if (isZeroSquare && size > maxSize) {
        maxSize = size;
        resX = x;
        resY = y;
    }

    // if the current square block does not contain only zeros,
    // we search for the solution in the four sub-blocks of the
    // current square block
    int half = ceil(size / 2.0);
    findZeroSquare(x, y, half);
    findZeroSquare(x, y + half, half);
    findZeroSquare(x + half, y, half);
    findZeroSquare(x + half, y + half, half);
}

int main() {
    //fill the matrix
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            matrix[i][j] = rand() % 2;
    //print matrix
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++)
            std::cout << matrix[i][j] << " ";
        std::cout << std::endl;
    }

// call the findZeroSquare function to find a square block of zeros
// in the matrix starting from the top left corner (0, 0) with the
// maximum possible size
    findZeroSquare(0, 0, std::min(M, N));
    std::cout << "Found a square block of zeros at (" << resX << ", " << resY << ") with size " << maxSize << std::endl;

    return 0;
}
*/
/* v2

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N=8;
const int M=8;
int a[N][N];
int res = 0;
int rCoord[2];

// check if the submatrix starting at (x, y) with size k x k
// contains only zeros
bool check(int x, int y, int k) {
    for (int i = x; i < x+k; i++) {
        for (int j = y; j < y+k; j++) {
            if (a[i][j] == 1) return false;
        }
    }
    return true;
}

// find the maximum size of a square submatrix containing only zeros
void solve(int x, int y, int k) {
    // if the submatrix is out of bounds, return
    if (x + k > N || y + k > M) return;

    // if the submatrix contains only zeros, update the result
    if (check(x, y, k)) {
        if (k > res) {
            res = k;
            rCoord[0] = x;
            rCoord[1] = y;
        }

        // continue searching in the right and down directions
        solve(x, y + 1, k);
        solve(x + 1, y, k);
    }

        // if the submatrix contains a 1, try a smaller size
    else {
        solve(x, y, k - 1);
    }
}

int main() {
    // read the input
    //cin >> N >> M;
    bool flag = true;
    while (flag) {
        srand(time(NULL));
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                a[i][j] = (rand() % 2); //fill
            }
        }
        for (int i = 0; i < M - 1; i++) {
            for (int j = 0; j < N - 1; j++) { //check if there is a square with 0
                if (a[i][j] == 0 && a[i][j + 1] == 0 && a[i + 1][j] == 0 && a[i + 1][j + 1] == 0) {
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
            cout << a[i][j] << " ";
        }
        cout << endl;
    }

    // search for the maximum size square submatrix
    solve(0, 0, min(N,M));

    // print the result
    cout << res << endl;
    cout << rCoord[0] << " " << rCoord[1] << endl;

    return 0;
}

*/
/*
#include <iostream>

using namespace std;

#include <cstdlib>
#include <cmath>
#include <vector>


//write algorithm which using breach and bound for searching max square filled with 0 in block and print out his coordinates and size
void branchandbound(int M, int N, vector<vector<int>> block, int square) {
    if (M > square || N > square) {
        for (int io = 0; io < 2; io++) {
            for (int jo = 0; jo < 2; jo++) {
                int newM = ceil(M / 2.0);
                int newN = ceil(N / 2.0);
                vector<vector<int>> slice(newM, vector<int>(newN));
                for (int i = 0; i < newM; i++) {
                    for (int j = 0; j < newN; j++) {
                        slice.at(i).at(j) = block[i + io * newM][j + jo * newM];
                    }
                }
                //print vector<vector<int>> slice
                cout << endl << "slice" << endl;
                for (int i = 0; i < newM; i++) {
                    for (int j = 0; j < newN; j++) {
                        cout << slice[i][j] << " ";
                    }
                    cout << endl;
                }
                branchandbound(newM, newN, slice, square);
            }
        }
    }
}


int main() {
    int M = 6, N = 6;
    // cin >> M >> N;
    vector<vector<int>> block(M, vector<int>(N));
    bool flag = true;
    while (flag) {
        srand(time(NULL));
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                block.at(i).at(j) = (rand() % 2); //fill
            }
        }
        for (int i = 0; i < M - 1; i++) {
            for (int j = 0; j < N - 1; j++) { //check if there is a square with 0
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

    branchandbound(M, N, block, 2);
    return 0;
}
*/