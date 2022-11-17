#ifndef BINARY_H
#define BINARY_H

template<class fileStream>
void openFile(fileStream &file, std::string FILE_NAME, const std::string &dir = "in", const std::string &type = "txt");

void createTxtFile(const std::string &txtFileName);

void createBinFromTxt(const std::string &txtFileName, const std::string &binFileName);

void addEntryInBin(const string &binFileName, groupElement entry = *new groupElement());

groupElement getEntryFromBin(const string &binFileName, int order = 0);

void deleteEntryByKey(int groupId, const string &binFileName);

int getFileLength(const std::string &binFileName);

#endif //BINARY_H
