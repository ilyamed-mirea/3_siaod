#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

using namespace std;

#include "hashTable.h"
#include "binary.h"

template<class fileStream>
void openFile(fileStream &file, string FILE_NAME, const string &dir, const string &type) {
    while (!file.is_open() || !file) {
        if (type == "binary") {
            if (dir == "in") file.open(FILE_NAME, ios::in | ios::binary);
            else if (dir == "out") file.open(FILE_NAME, ios::out | ios::binary);
            else file.open(FILE_NAME, std::ios::in | std::ios::out | std::ios::app | std::ios::binary);
        } else file.open(FILE_NAME);
        if (!file.is_open() || !file) {
            cout << "error occured while openning the file. write any number to try again or write 0 to exit." << endl;
            int r;
            cin >> r;
            if (r == 0)
                break;
        } else break;
    }
}

int getFileLength(const string &binFileName) {
    fstream file;
    file.open(binFileName, ios::in | ios::out | ios::binary);
    groupElement entry;
    int fileLength = 0;
    while (file.read((char *) &entry, sizeof(entry))) {
        fileLength++;
    }
    file.close();
    return fileLength;
}

void createTxtFile(const string &txtFileName) {
    ofstream file;
    //cout << "write file name";
    //getline(cin,fileName);
    openFile(file, txtFileName);
    //cout << "write 0 for default values or 1 for manual input?" << endl;
    //int ind;
    //cin >> ind;
    //int groupId; double medianScore; int studentCount; int predmetId;
    file << 12 << endl << 4.2 << endl << 28 << endl << 1 << endl;
    file << 14 << endl << 3 << endl << 15 << endl << 3 << endl;
    file << 112 << endl << 4.2 << endl << 28 << endl << 2 << endl;
    file << 25 << endl << 3.6 << endl << 30 << endl << 2 << endl;
    file << 66 << endl << 4.9 << endl << 25 << endl << 6 << endl;

    file << 11 << endl << 2.1 << endl << 7 << endl << 1 << endl;
    file << 3 << endl << 2.0 << endl << 6 << endl << 3 << endl;
    file << 255 << endl << 2.2 << endl << 5 << endl << 5 << endl;
    file << 666 << endl << 2.3 << endl << 4 << endl << 4 << endl;
    file << 1232 << endl << 2.9 << endl << 3 << endl << 6;
    file.close();
}

void createBinFromTxt(const string &txtFileName, const string &binFileName) {
    ifstream readFile;
    openFile(readFile, txtFileName);
    fstream writeFile(binFileName, ios::in | ios::out | ios::binary | ios::trunc); //clear file
    writeFile.close();

    groupElement groupElement;
    while (readFile >> groupElement.groupId >> groupElement.medianScore >> groupElement.studentCount
                    >> groupElement.predmetId) {
        addEntryInBin(binFileName, groupElement);
    }
    readFile.close();
}

void printOutBinFile(const std::string &binFileName) {
    fstream file;
    openFile(file, binFileName, "in", "bin");
    groupElement temp;
    while (file.read((char *) &temp, sizeof(groupElement))) {
        cout << temp.groupId << endl;
    }
    file.close();
}

void addEntryInBin(const string &binFileName, groupElement entry) {
    ofstream writeFile;
    openFile(writeFile, binFileName, "app", "binary");
    writeFile.write((char *) &entry, sizeof(groupElement));
    writeFile.close();
}

groupElement getEntryFromBin(const string &binFileName, int order) {
    ifstream readFile;
    openFile(readFile, binFileName, "in", "binary");
    groupElement entry;
    readFile.seekg(sizeof(groupElement) * order, ios::beg);
    readFile.read((char *) &entry, sizeof(groupElement));
    readFile.close();
    return entry;
}

int deleteEntryByKey(int groupId, const string &binFileName) {
    groupElement entry;
    groupElement lastEntry;
    fstream file;
    file.open(binFileName, ios::in | ios::out | ios::binary);
    file.seekg(-1 * sizeof(groupElement), ios::end);
    int sizeWithoutLast = file.tellg();
    file.read((char *) &lastEntry, sizeof(groupElement));
    file.seekg(0, ios::beg);

    int i = 0;
    while (file.read((char *) &entry, sizeof(groupElement)) && entry.groupId != groupId) {
        i++;
    }

    file.seekg(i * sizeof(groupElement), ios::beg);
    file.write((char *) &lastEntry, sizeof(groupElement));

    file.seekg(0, std::ios::beg);
    std::filesystem::resize_file(binFileName, sizeWithoutLast);
    file.close();

    return i;
}