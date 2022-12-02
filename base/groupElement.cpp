//
// Created by ilyaMedvedev on 02.12.2022.
//
#include "groupElement.h"
#include <iostream>

groupElement::groupElement() {
    srand(time(nullptr));
    groupId = rand() % 100;
    medianScore = -1;
    studentCount = -1;
}

groupElement::groupElement(int groupId) {
    this->groupId = groupId;
    this->medianScore = -1;
    this->studentCount = -1;
}

groupElement::groupElement(int groupId, double medianScore, int studentCount) {
    this->groupId = groupId;
    this->medianScore = medianScore;
    this->studentCount = studentCount;
}

