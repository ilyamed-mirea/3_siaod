#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const bool testMode = true;

template <class fileStream>
void checkFileOpen(fileStream& file, string FILE_NAME) {
	while (!file.is_open()) {
		file.open(FILE_NAME);
		cout << "error occured while openning the file. try again" << endl;
		int r;
		cin >> r;
		if (r == 0)
			break;
	}
}

void createAndFillFile(ofstream& file, string FILE_NAME) {
	file.open(FILE_NAME);
	checkFileOpen(file, FILE_NAME);

	if (testMode) {
		for (int i = 1; i <= 10; i++) {
			if (i == 4) continue;
			file << i << ' ';
			if (i % 3 == 0) file << endl;
		}
	}
	else {
		cout << "how many numbers?" << endl;
		int colv;
		cin >> colv;
		cout << "how many in 1 row?" << endl;
		int row;
		cin >> row;
		for (int i = 0; i < colv; i++) {
			cout << "write " << i+1 << " num: ";
			int x;
			cin >> x;
			file << x << ' ';
			if ((i+1) % row == 0) file << endl;
		}
	}
	file.close();
}

void printOutFile(ifstream& file, string FILE_NAME) {
	file.open(FILE_NAME);
	checkFileOpen(file, FILE_NAME);

	string line;
	while (!file.eof()) {
		getline(file, line);
		cout << line << endl;
	}
	file.close();
}

template <class valueToWrite>
void writeInFile(ofstream& file, string FILE_NAME, valueToWrite x) {
	file.open(FILE_NAME);
	checkFileOpen(file, FILE_NAME);
	file << x;
	file.close();
}

void readValueAtPos(ifstream& file, string FILE_NAME, int pos) {
	file.open(FILE_NAME);
	checkFileOpen(file, FILE_NAME);
	int x, i;
	for (i = 1; (i < pos && (!file.eof())); i++)
	{
		file >> x;
		file.get();
	}
	cout << "value at position " << pos << " is: ";
	while (!file.eof() && (i == pos))
	{
		file >> x;
		file.get();
		cout << x;
		i++;
	}
	cout << endl;
	file.close();
}

void countNumbers(ifstream& file, string FILE_NAME) {
	file.open(FILE_NAME);
	checkFileOpen(file, FILE_NAME);
	int x, counter = 0;
	while (file >> x) counter++;
	cout << counter << " numbers in file" << endl;
	file.close();
}

void variantTask(ofstream& ofile, ifstream& ifile, string FILE_NAME) {
    const string NEW_FILE_NAME = "newFile.txt";
    ofile.open(NEW_FILE_NAME);
    checkFileOpen(ofile,NEW_FILE_NAME);
	ifile.open(FILE_NAME);
    checkFileOpen(ifile, FILE_NAME);

    while (!ifile.eof()) {
        int x, length = 0;
        ifile >> x;
        if (x==0) length=1;
        for (int i=x;i>0;i/=10,length++);
        ofile << x << " " << length << endl;
    }
    ifile.close();
    ofile.close();
}

int main() {
	system("chcp 65001");
	//setlocale(LC_ALL, "Russian");

	string FILE_NAME;
	if (testMode) {
		FILE_NAME = "f.txt";
	}
	else {
		cin >> FILE_NAME;
	}

	int menu = 1;

	ifstream fread;
	ofstream fwrite;

	cout << "Medvedev I.V. INBO-08-21" << endl;
	while (menu != 0) {
		cout << "-----------------------------------------------------" << endl;
		cout << "1) create and fill file" << endl;
		cout << "2) print file" << endl;
		cout << "3) print value at position" << endl;
		cout << "4) count numbers in file" << endl;
		cout << "5) variant task" << endl;
		cout << "0) exit" << endl;
		cin >> menu;
		switch (menu) {
		case 0:
			return 0;
		case 1:
			createAndFillFile(fwrite, FILE_NAME);
			break;
		case 2:
			printOutFile(fread, FILE_NAME);
			break;
		case 3:
			int pos;
			cin >> pos;
			readValueAtPos(fread, FILE_NAME, pos);
			break;
		case 4:
			countNumbers(fread, FILE_NAME);
			break;
		case 5:
			variantTask(fwrite, fread, FILE_NAME);
			break;
		default:
			break;
		}
	}

	//system("pause");

	return 0;
}