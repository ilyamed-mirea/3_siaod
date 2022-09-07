#include <iostream>
#include <vector>
#include <array>

using namespace std;

int getDots(vector<array<int, 2>> &points) { //ввод точек
    cout << "Сколько вы хотите ввести точек? (минимум 9)" << endl;
    int dotsCount;
    while (true) {
        cin >> dotsCount;
        if (cin.fail() || cin.peek() != '\n' || dotsCount<9) {
            cin.clear();
            cin.ignore(32777, '\n');
            if (dotsCount<9)
                cout << "Слишком мало точек, повторите ввод" << endl;
            else
                cout << "Ошибка ввода. Пожалуйста, повторите..." << endl;
        } else break;
    }
    points.reserve(dotsCount);
    for (int i = 0; i < dotsCount; i++) {
        array<int, 2> dot{0,0};
        while (true) {
            cout << "write x" << i << " : ";
            cin >> dot[0];
            if (cin.fail() || cin.peek() != '\n') {
                cin.clear();
                cin.ignore(32777, '\n');
                cout << "Ошибка ввода. Пожалуйста, повторите..." << endl;
            } else break;
        }
        while (true) {
            cout << "write y" << i << " : ";
            cin >> dot[1];
            if (cin.fail() || cin.peek() != '\n') {
                cin.clear();
                cin.ignore(32777, '\n');
                cout << "Ошибка ввода. Пожалуйста, повторите..." << endl;
            } else break;
        }
        points.push_back(dot);
    }
    return dotsCount;
}

bool checkTriangle(array<int, 2> p0, array<int, 2> p1, array<int, 2> p2) { // проверка, существует ли треугольник
    return ((p0[0] * (p1[1] - p2[1]) +
             p1[0] * (p2[1] - p0[1]) +
             p2[0] * (p0[1] - p1[1])) != 0);
}

bool PointInTriangle(array<int, 2> p, array<int, 2> p0, array<int, 2> p1, array<int, 2> p2) { // проверка, входит ли точка в треугольник

    if (!checkTriangle(p0, p1, p2) || p[0] == p0[0] && p[1] == p0[1] || p[0] == p1[0] && p[1] == p1[1] || p[0] == p2[0] && p[1] == p2[1])
        return false;

    int s = (p0[0] - p2[0]) * (p[1] - p2[1]) - (p0[1] - p2[1]) * (p[0] - p2[0]);
    int t = (p1[0] - p0[0]) * (p[1] - p0[1]) - (p1[1] - p0[1]) * (p[0] - p0[0]);
    // барицентрические координаты

    if ((s < 0) != (t < 0) && s != 0 && t != 0)
        return false;

    int d = (p2[0] - p1[0]) * (p[1] - p1[1]) - (p2[1] - p1[1]) * (p[0] - p1[0]);
    return d == 0 || ((d < 0) == (s + t <= 0));
}

bool PointOnLine(array<int, 2> p, array<int, 2> p0, array<int, 2> p1) { // проверка, лежит ли точка на прямой
    if (p1[0] == p0[0]) {
        return (p[0] == p0[0] && p[1] >= min(p0[1], p1[1]) && p0[0] <= max(p0[1], p1[1]));
    }

    int k = (p1[1] - p0[1]) / (p1[0] - p0[0]);
    int c = p0[1] - k * p0[0];

    return p[1] == p[0] * k + c;
}


void findTriangles(vector<array<int, 2>> points, vector<vector<array<int, 2>>> &results, int dotsCount) { // нахождение 3 подходящих под условие треугольников
    bool fl = true;
    for (int i = 0; i < dotsCount - 2; i++) {
        if (fl)
            for (int j = i + 1; j < dotsCount - 1; j++) {
                if (fl)
                    for (int k = j + 1; k < dotsCount; k++) {
                        vector<array<int, 2>> triang1;
                        vector<array<int, 2>> triang2;
                        vector<array<int, 2>> triang3;
                        triang1.push_back(points[i]);
                        triang1.push_back(points[j]);
                        triang1.push_back(points[k]);

                        for (int z = 0; z < dotsCount - 2; z++) {
                            if (PointInTriangle(points[z], triang1[0], triang1[1], triang1[2]) && fl && z != i &&
                                z != j && z != k) {
                                for (int x = z + 1; x < dotsCount - 1; x++) {
                                    if (PointInTriangle(points[x], triang1[0], triang1[1], triang1[2]) && fl &&
                                        x != i && x != j &&
                                        x != k) {
                                        for (int c = x + 1; c < dotsCount; c++) {
                                            if (PointInTriangle(points[c], triang1[0], triang1[1], triang1[2]) && fl &&
                                                c != i &&
                                                c != j && c != k) {
                                                if (PointOnLine(points[z], triang1[0], triang1[1]) || PointOnLine(points[z], triang1[0], triang1[2]) || PointOnLine(points[z], triang1[1], triang1[2])
                                                || PointOnLine(points[x], triang1[0], triang1[1]) || PointOnLine(points[x], triang1[0], triang1[2]) || PointOnLine(points[x], triang1[1], triang1[2])
                                                || PointOnLine(points[c], triang1[0], triang1[1]) || PointOnLine(points[c], triang1[0], triang1[2]) || PointOnLine(points[c], triang1[1], triang1[2])
                                                ) break;
                                                triang2.push_back(points[z]);
                                                triang2.push_back(points[x]);
                                                triang2.push_back(points[c]);

                                                for (int q = 0; q < dotsCount - 2; q++) {
                                                    if (PointInTriangle(points[q], triang2[0], triang2[1],
                                                                        triang2[2]) && fl &&
                                                        q != i && q != j && q != k && q != z && q != x && q != c) {
                                                        for (int w = q + 1; w < dotsCount - 1; w++) {
                                                            if (PointInTriangle(points[w], triang2[0], triang2[1],
                                                                                triang2[2]) && fl && w != i && w != j &&
                                                                w != k &&
                                                                w != z && w != x && w != c) {
                                                                for (int e = w + 1; e < dotsCount; e++) {
                                                                    if (PointInTriangle(points[e], triang2[0],
                                                                                        triang2[1],
                                                                                        triang2[2]) && e != i &&
                                                                        e != j &&
                                                                        e != k && e != z && e != x && e != c) {
                                                                        if (PointOnLine(points[q], triang2[0], triang2[1]) || PointOnLine(points[q], triang2[0], triang2[2]) || PointOnLine(points[q], triang2[1], triang2[2])
                                                                            || PointOnLine(points[w], triang2[0], triang2[1]) || PointOnLine(points[w], triang2[0], triang2[2]) || PointOnLine(points[w], triang2[1], triang2[2])
                                                                            || PointOnLine(points[e], triang2[0], triang2[1]) || PointOnLine(points[e], triang2[0], triang2[2]) || PointOnLine(points[e], triang2[1], triang2[2])
                                                                            ||
                                                                                PointOnLine(points[q], triang1[0], triang1[1]) || PointOnLine(points[q], triang1[0], triang1[2]) || PointOnLine(points[q], triang1[1], triang1[2])
                                                                                || PointOnLine(points[w], triang1[0], triang1[1]) || PointOnLine(points[w], triang1[0], triang1[2]) || PointOnLine(points[w], triang1[1], triang1[2])
                                                                                || PointOnLine(points[e], triang1[0], triang1[1]) || PointOnLine(points[e], triang1[0], triang1[2]) || PointOnLine(points[e], triang1[1], triang1[2])
                                                                            ) break;
                                                                        triang3.push_back(points[q]);
                                                                        triang3.push_back(points[w]);
                                                                        triang3.push_back(points[e]);

                                                                        results.push_back(triang1);
                                                                        results.push_back(triang2);
                                                                        results.push_back(triang3);

                                                                        fl = false;
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
}

void printResults(const vector<vector<array<int, 2>>> &results) { // вывод результатов
    int cou = 1;
    for (vector<array<int, 2>> i: results) {
        cout << endl << "Треугольник N " << cou << endl;
        for (int k = 0; k < 3; k++) {
            for (int f = 0; f < 2; f++) {
                cout << i[k][f] << " ";
            }
            cout << endl;
        }
        cou++;
    }
    if (cou == 1) cout << "Треугольники не найдены :(" << endl;
}

int main() {
    system("chcp 65001");
    vector<array<int, 2>> points;
    vector<vector<array<int, 2>>> results;

    int dotsCount = getDots(points);
    findTriangles(points, results, dotsCount);
    printResults(results);

    system("pause");
    return(0);
}


/*
float area(int x1, int y1, int x2, int y2, int x3, int y3) {
    return abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2);
}

 A function to check whether point P(x, y) lies inside the triangle formed
   by A(x1, y1), B(x2, y2) and C(x3, y3)
bool isInside(array<int, 2> p, array<int, 2> p0, array<int, 2> p1, array<int, 2> p2) {
    if (!checkTriangle(p0, p1, p2) || p[0] == p0[0] || p[0] == p1[0] || p[0] == p2[0] || p[1] == p0[1] ||
        p[1] == p1[1] || p[1] == p2[1])
        return false;


    int x1 = p0[0];
    int y1 = p0[1];
    int x2 = p1[0];
    int y2 = p1[1];
    int x3 = p2[0];
    int y3 = p2[1];
    int x = p[0];
    int y = p[1];

    // Calculate area of triangle ABC
    float A = area(x1, y1, x2, y2, x3, y3);

    // Calculate area of triangle PBC
    float A1 = area(x, y, x2, y2, x3, y3);

    // Calculate area of triangle PAC
    float A2 = area(x1, y1, x, y, x3, y3);

    // Calculate area of triangle PAB
    float A3 = area(x1, y1, x2, y2, x, y);

    // Check if sum of A1, A2 and A3 is same as A
    return (A == A1 + A2 + A3);
}
*/









