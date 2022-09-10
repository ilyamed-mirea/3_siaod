#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const bool testMode = true;

template <class fileStream>
void checkFileOpen(fileStream& file, string FILE_NAME) {
	while (!file.is_open()) {
		file.open(FILE_NAME);
		cout << "Ошибка при открытии файла. введите 1 для повторной попытки или 0 для завершения" << endl;
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
		cout << "Сколько чисел хотите ввести?" << endl;
		int colv;
		cin >> colv;
		cout << "Сколько чисел будет в ряду?" << endl;
		int row;
		cin >> row;
		for (int i = 0; i < colv; i++) {
			cout << "Введите " << i << " число: ";
			int x;
			cin >> x;
			file << x << ' ';
			if (i % row == 0) file << endl;
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
	while (!file.eof())
	{
		file >> x;
		counter++;
		file.get();
	}
	cout << counter << " numbers in file" << endl;
	file.close();
}

void variantTask(ofstream& ofile, ifstream& ifile, string FILE_NAME) {
	ifile.open("newFile.txt");
	ofile.open(FILE_NAME);

}

int main() {
	//system("chcp 65001");
	setlocale(LC_ALL, "Russian");

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

	cout << "Медведев И.В. ИНБО-08-21" << endl;
	while (menu != 0) {
		cout << "-----------------------------------------------------" << endl;
		cout << "Для создания файла и заполнения его числами введите 1" << endl;
		cout << "Для вывода файла в консоль введите 2" << endl;
		cout << "Для вывода значения с определенной позиции введите 3" << endl;
		cout << "Для вывода количества чисел в файле введите 4" << endl;
		cout << "Для выполнения задачи варианта введите 5" << endl;
		cout << "Для выхода введите 0" << endl;
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
			variantTask(fread, FILE_NAME);
			break;
		default:
			break;
		}
	}

	//system("pause");

	return 0;
}