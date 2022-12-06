//
// Created by 0ilya on 04.12.2022.
//

#include <vector>
#include <list>
#include "Graph.h"

#include "iostream"

using namespace std;

Edge::Edge(int v, int w) {
    this->v = v;
    this->w = w;
}

Graph::Graph(int N) {
    V = N + 1;
    E = 0;
    Matr = new int *[V];
    for (int i = 0; i < V; i++) {
        Matr[i] = new int[V];
        for (int j = 0; j < V; j++) {
            Matr[i][j] = 0;
        }
    }
}

Graph::~Graph() {
    for (int i = 0; i < V; i++)
        delete[] Matr[i];
    delete[] Matr;
}

void Graph::addEdge(Edge edge) {
    int v = edge.v, w = edge.w;
    if (Matr[v][w] == 0) E++;
    Matr[v][w] = 1;
    //Matr[w][v] = 1;
}

void Graph::removeEdge(Edge edge) {
    int v = edge.v, w = edge.w;
    if (Matr[v][w] == 1) E--;
    Matr[v][w] = 0;
    //Matr[w][v] = 0;
}

void Graph::printGraph() {
    cout << "Graph:" << endl;
    cout << "    ";
    for (int i = 1; i < V; i++) {
        cout << i << " ";
    }
    cout << endl;
    for (int i = 1; i < V; i++) {
        cout << i << " : ";
        for (int j = 1; j < V; j++)
            cout << Matr[i][j] << " ";
        cout << "\n";
    }
}

void Graph::dfs(int v, int *&L) {
    int w; // смежная вершина
    L[v] = 1; // признак прохождения вершины
    for (w = 1; w < V; w++)
        if (Matr[v][w] == 1 && L[w] == -1) {
            cout << "->" << w;
            dfs(w, L);
        }
}

int Graph::findRoot() {
    int *L;
    int res;
    for (int v = 1; v < V; v++) {
        L = new int[V];
        for (int i = 1; i < V; i++) // заполняем список не посещенных вершин
            L[i] = -1;
        cout << v;
        dfs(v, L);
        bool LNotFull = true;
        for (int i = 1; i < V; i++) {
            if (L[i] == -1) {
                LNotFull = true;
                break;
            }
            LNotFull = false;
        }
        if (LNotFull)
            cout << " - not correct" << endl;
        else {
            res = v;
            cout << " - correct!" << endl;
        }
    }
    delete[] L;
    return res;
}

void Graph::printGraphList() {
    cout << endl << "Graph:" << endl;
    for (int i = 1; i < V; i++) {
        cout << i << " : ";
        for (int j = 1; j < V; j++)
            if (Matr[i][j] == 1)
                cout << "{" << i << "; " << j << "} ";
        cout << "\n";
    }
}

void Graph::dfs2(int a, int b, vector<vector<int>> &routes, vector<int> route) {
    route.push_back(a);
    if (a == b)
        routes.push_back(route);
    else
        for (int i = 1; i < V; i++)
            if (Matr[a][i] == 1 && std::find(route.begin(), route.end(), i) == route.end())
                dfs2(i, b, routes, route);
}

vector<vector<int>> Graph::findAllRoutes(int a, int b) {
    vector<vector<int>> routes;
    vector<int> route;
    dfs2(a, b, routes, route);
    return routes;
}

int Graph::findMaxRoute() {
    int max = 0;
    vector<int> longestRoute;
    for (int a = 0; a < V; a++) {
        for (int b = 0; b < V; b++) {
            vector<vector<int>> routes = findAllRoutes(a, b);
            for (int i = 0; i < routes.size(); i++) {
                if (routes[i].size() > max) {
                    longestRoute = routes[i];
                    max = routes[i].size() - 1;
                }
            }
        }
    }
    cout << "Longest route: " << longestRoute.front() << " -> " << longestRoute.back() << " (" << max << ")" << endl;
    return max;
}

void Graph::shortestPath(int a, int b) {
    vector<vector<int>> routes = findAllRoutes(a, b);
    vector<int> shortestRoute;
    int min = INT32_MAX;
    for (int i = 0; i < routes.size(); i++) {
        if (routes[i].size() - 1 < min) {
            shortestRoute = routes[i];
            min = routes[i].size() - 1;
        }
    }
    cout << "Shortest path between " << a << " and " << b << ":" << endl;
    for (int i = 0; i < shortestRoute.size() && (i == 0 || cout << " -> "); i++) {
        cout << shortestRoute[i];
    }
    cout << " (" << min << ")" << endl;
}