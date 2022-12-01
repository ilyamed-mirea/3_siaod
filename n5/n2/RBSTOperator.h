//
// Created by ilyaMedvedev on 01.12.2022.
//

#ifndef INC_3_SIAOD_RBSTOperator_H
#define INC_3_SIAOD_RBSTOperator_H

#include "RBST.cpp"
#include "binary.cpp"

void fillTreeFromBin(Tree &tree, std::string binFileName);
void removeEntry(Tree &tree, const std::string &binFileName, int groupId);
//void findInTree(Tree &tree, std::string binFileName);
groupElement findInBinByKey(Tree &tree, int groupId, const std::string &binFileName);
void addEntry(Tree &tree, const std::string &binFileName, groupElement element);

#endif //INC_3_SIAOD_RBSTOperator_H
