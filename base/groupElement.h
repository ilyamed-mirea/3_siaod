//
// Created by ilyaMedvedev on 02.12.2022.
//

#ifndef INC_3_SIAOD_GROUPELEMENT_H
#define INC_3_SIAOD_GROUPELEMENT_H


struct groupElement {
    int groupId;
    double medianScore;
    int studentCount;

    groupElement();

    groupElement(int groupId);

    groupElement(int groupId, double medianScore, int studentCount);
};


#endif //INC_3_SIAOD_GROUPELEMENT_H
