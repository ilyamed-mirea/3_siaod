//
// Created by ilyaMedvedev on 01.12.2022.
//

#ifndef INC_3_SIAOD_RBSTOperator_H
#define INC_3_SIAOD_RBSTOperator_H

#include "RBST.cpp"
#include "binary.cpp"

void fillTreeFromBin(RBSTTRee &tree, std::string binFileName);
void removeEntry(RBSTTRee &tree, const std::string &binFileName, int groupId);
groupElement findInBinByKey(RBSTTRee &tree, int groupId, const std::string &binFileName);
void addEntry(RBSTTRee &tree, const std::string &binFileName, groupElement element);
int countRotating();

#endif //INC_3_SIAOD_RBSTOperator_H
