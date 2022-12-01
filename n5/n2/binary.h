#ifndef BINARYRB_H
#define BINARYRB_H

using namespace std;

struct groupElement {
    int groupId;
    double medianScore;
    int studentCount;

    groupElement();

    groupElement(int groupId);

    groupElement(int groupId, double medianScore, int studentCount);
};


template<class fileStream>
void openFile(fileStream &file, std::string FILE_NAME, const std::string &dir = "in", const std::string &type = "txt");

void createTxtFile(const std::string &txtFileName);

void createBinFromTxt(const std::string &txtFileName, const std::string &binFileName);

void printOutBinFile(const std::string &binFileName);

void addEntryInBin(const string &binFileName, groupElement entry = *new groupElement());

groupElement getEntryFromBin(const string &binFileName, int order = 0);

int deleteEntryByKey(int groupId, const string &binFileName);

int getFileLength(const std::string &binFileName);

void clearBinFile(const std::string &binFileName);

#endif //BINARYRB_H
