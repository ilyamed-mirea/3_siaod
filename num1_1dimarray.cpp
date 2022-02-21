#include <iostream>
#include <string>
#include "Header.h"
using namespace std;

string to2(int x) {
	string res = "";
	while (x > 0) {
		res += to_string(x % 2);
		x = x / 2;
	}
	return res;
}

int* getArr() {
	int length;
	cout << "write array length" << endl;
	cin >> length;
	int* arr = new int[length];
	cout << "write values" << endl;
	for (int i = 0; i < length; i++) {
		cin >> arr[i];
	}
	return arr;
}

void printArr(int *arr, int length) {
	cout << "your array:" << endl;
	for (int i = 0; i < length; i++) {
		cout << arr[i] << endl;
	}
	cout << "array end" << endl;
}

int num1() {
	//initialize
	int *arr = getArr(); //{ 5,273,6,7,8,2340 }; 273 = три единицы
	printArr(arr, 4);
	//n1
	for (int i = 0; i < 6; i++) {
		string in2 = to2(arr[i]);
		int colv1 = 0;
		for (int j = 0; j < in2.length(); j++) {
			if (in2[j] == '1') {
				colv1++;
			}
		}
		if (colv1 == 3) {
			cout << i << endl;
			break;
		}
	}

	//n2

	return 0;
}