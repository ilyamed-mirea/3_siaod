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

int num1() {
	//initialize
	int length = 5;
	int *arr = new int[length];
	arr[0] = 5; arr[2] = 6; arr[1] = 7;

	//n1
	for (int i = 0; i < length; i++) {
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