#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const bool testMode = true;

template<class fileStream>
void checkFileOpen(fileStream &file, string FILE_NAME);

void createAndFillFile(ofstream &file, string FILE_NAME);

void printOutFile(ifstream &file, string FILE_NAME);

template<class valueToWrite>
void writeInFile(ofstream &file, string FILE_NAME, valueToWrite x);

int readValueAtPos(ifstream &file, string FILE_NAME, int pos);

void countNumbers(ifstream &file, string FILE_NAME);

void variantTask(ofstream &ofile, ifstream &ifile, string FILE_NAME);

template<class fileStream>
void checkFileOpen(fileStream &file, string FILE_NAME) {
    while (!file.is_open()) {
        file.open(FILE_NAME);
        cout << "error occured while openning the file. try again" << endl;
        int r;
        cin >> r;
        if (r == 0)
            break;
    }
}

void createAndFillFile(ofstream &file, string FILE_NAME) {
    file.open(FILE_NAME);
    checkFileOpen(file, FILE_NAME);

    if (testMode) {
        for (int i = 1; i <= 10; i++) {
            srand(time(0));
            if (i == 4) continue;
            file << i * rand() % 100 << ' ';
            if (i % 3 == 0) file << endl;
        }
    } else {
        cout << "how many numbers?" << endl;
        int colv;
        cin >> colv;
        cout << "how many numbers in 1 row?" << endl;
        int row;
        cin >> row;
        for (int i = 0; i < colv; i++) {
            cout << "write " << i + 1 << " num: ";
            int x;
            cin >> x;
            file << x << ' ';
            if ((i + 1) % row == 0) file << endl;
        }
    }
    file.close();
}

void printOutFile(ifstream &file, string FILE_NAME) {
    file.open(FILE_NAME);
    checkFileOpen(file, FILE_NAME);

    string line;
    while (!file.eof()) {
        getline(file, line);
        cout << line << endl;
    }
    file.close();
}

template<class valueToWrite>
void writeInFile(ofstream &file, string FILE_NAME, valueToWrite x) {
    file.open(FILE_NAME);
    checkFileOpen(file, FILE_NAME);
    file << x;
    file.close();
}

int readValueAtPos(ifstream &file, string FILE_NAME, int pos) {
    file.open(FILE_NAME);
    checkFileOpen(file, FILE_NAME);
    int x, i;
    for (i = 1; (i <= pos && !file.eof()); i++) {
        file >> x;
    }
    file.close();
    cout << "value at position " << pos << " is: ";
    cout << x << endl;
    return x;
}

void countNumbers(ifstream &file, string FILE_NAME) {
    file.open(FILE_NAME);
    checkFileOpen(file, FILE_NAME);
    int x, counter = 0;
    while (file >> x) counter++;
    cout << counter << " numbers in file" << endl;
    file.close();
}

void variantTask(ofstream &ofile, ifstream &ifile, string FILE_NAME) {
    string NEW_FILE_NAME;
    if (testMode)
        NEW_FILE_NAME = "newFile.txt";
    else {
        cout << " write new file name" << endl;
        cin >> NEW_FILE_NAME;
    }
    ofile.open(NEW_FILE_NAME);
    checkFileOpen(ofile, NEW_FILE_NAME);
    ifile.open(FILE_NAME);
    checkFileOpen(ifile, FILE_NAME);

    while (!ifile.eof()) {
        int x, length = 0;
        ifile >> x;
        if (x == 0) length = 1;
        for (int i = x; i > 0; i /= 10, length++);
        ofile << x << " " << length << endl;
    }
    ifile.close();
    ofile.close();
    printOutFile(ifile, NEW_FILE_NAME);
}

int main() {
    system("chcp 65001");
    //setlocale(LC_ALL, "Russian");

    string FILE_NAME;
    if (testMode)
        FILE_NAME = "n1.txt";
    else
        cin >> FILE_NAME;

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
                if (!fread.good() || !fwrite.good())
                    cout << "error in files" << endl;
                return 0;
            case 1:
                createAndFillFile(fwrite, FILE_NAME);
                break;
            case 2:
                printOutFile(fread, FILE_NAME);
                break;
            case 3:
                int pos;
                cout << "write pos: ";
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
                menu = 1;
                break;
        }
    }
}