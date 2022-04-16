#include <iostream>
#include <vector>
#include <array>
#include <ctime>
using namespace std;

int getDots(vector<array<int, 2>> &points) {
    cout << "Сколько вы хотите ввести точек?" << endl;
    int dotsCount;
    while (true) {
        cin >> dotsCount;
        if (cin.fail() || cin.peek() != '\n' || dotsCount<9) {
            cin.clear();
            cin.ignore(32777, '\n');
            cout << "Ошибка ввода. Пожалуйста, повторите..." << endl;
        }
        else break;
    }
    points.reserve(dotsCount);
    for (int i=0;i<dotsCount;i++) {
        array<int, 2> dot;
        while (true) {
            cout << "write x" << i << " : ";
            cin >> dot[0];
            if (cin.fail() || cin.peek() != '\n') {
                cin.clear();
                cin.ignore(32777, '\n');
                cout << "Ошибка ввода. Пожалуйста, повторите..." << endl;
            }
            else break;
        }
        while (true) {
            cout << "write y" << i << " : ";
            cin >> dot[1];
            if (cin.fail() || cin.peek() != '\n') {
                cin.clear();
                cin.ignore(32777, '\n');
                cout << "Ошибка ввода. Пожалуйста, повторите..." << endl;
            }
            else break;
        }
        points.push_back(dot);
    }
    return dotsCount;
}

bool PointInTriangle(array<int,2> p, array<int,2> p0, array<int,2> p1, array<int,2> p2)
{
    int s = (p0[0] - p2[0]) * (p[1] - p2[1]) - (p0[1] - p2[1]) * (p[0] - p2[0]);
    int t = (p1[0] - p0[0]) * (p[1] - p0[1]) - (p1[1] - p0[1]) * (p[0] - p0[0]);

    if ((s < 0) != (t < 0) && s != 0 && t != 0)
        return false;

    int d = (p2[0] - p1[0]) * (p[1] - p1[1]) - (p2[1] - p1[1]) * (p[0] - p1[0]);
    return d == 0 || ((d < 0) == (s + t <= 0));
}

int main() {
    system("chcp 65001");
    vector<array<int, 2>> points;
    vector<vector<array<int, 2>>> results;
    int dotsCount = getDots(points);

    bool fl = true;
    for(int i = 0; i < dotsCount - 2; i++)
    {
        if (fl)
        for(int j = i + 1; j < dotsCount - 1; j++)
        {
            if (fl)
            for(int k = j + 1; k < dotsCount; k++)
            {
                vector<array<int, 2>> triang1;
                vector<array<int, 2>> triang2;
                vector<array<int, 2>> triang3;
                triang1.push_back(points[i]);
                triang1.push_back(points[j]);
                triang1.push_back(points[k]);

                for(int z = 0; z < dotsCount - 2; z++) {
                    if (PointInTriangle(points[z],triang1[0],triang1[1],triang1[2]) && fl && z!=i && z!=j && z!=k) {
                        for (int x = z + 1; x < dotsCount - 1; x++) {
                            if (PointInTriangle(points[x],triang1[0],triang1[1],triang1[2]) && fl && x!=i && x!=j && x!=k) {
                                for (int c = x + 1; c < dotsCount; c++) {
                                    if (PointInTriangle(points[c],triang1[0],triang1[1],triang1[2]) && fl && c!=i && c!=j && c!=k) {
                                        triang2.push_back(points[z]);
                                        triang2.push_back(points[x]);
                                        triang2.push_back(points[c]);

                                        for(int q = 0; q < dotsCount - 2; q++) {
                                            if (PointInTriangle(points[q],triang2[0],triang2[1],triang2[2]) && fl && q!=i && q!=j && q!=k && q!=z && q!=x && q!=c) {
                                                for (int w = q + 1; w < dotsCount - 1; w++) {
                                                    if (PointInTriangle(points[w],triang2[0],triang2[1],triang2[2]) && fl && w!=i && w!=j && w!=k && w!=z && w!=x && w!=c) {
                                                        for (int e = w + 1; e < dotsCount; e++) {
                                                            if (PointInTriangle(points[e],triang2[0],triang2[1],triang2[2]) && fl && e!=i && e!=j && e!=k && e!=z && e!=x && e!=c) {
                                                                triang3.push_back(points[q]);
                                                                triang3.push_back(points[w]);
                                                                triang3.push_back(points[e]);

                                                                results.push_back(triang1);
                                                                results.push_back(triang2);
                                                                results.push_back(triang3);

                                                                fl=false;
                                                                break;
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }

                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    cout << endl << "res" << endl;
    int cou=1;
    for (vector<array<int, 2>> i : results) {
        cout << endl << "triang " << cou << endl;
        for (int k=0;k<3;k++) {
            for (int f = 0;f<2;f++) {
                cout << i[k][f] << " ";
            }
            cout << endl;
        }
        cou++;
    }
    system("pause");
}