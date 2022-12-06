//
// Created by 0ilya on 04.12.2022.
//

#include <vector>
#include <list>
#include "Graph.h"

#include "iostream"

using namespace std;

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

Graph::~Graph() {
    for (int i = 0; i < V; i++)
        delete[] Matr[i];
    delete[] Matr;
}

void Graph::dfs(int v, int *&L) {
    int w; // смежная вершина
    L[v] = 1; // признак прохождения вершины
    for (w = 1; w < V; w++)
        if (Matr[v][w] == 1)
            if (L[w] == -1) {
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
    cout << "Graph:" << endl;
    for (int i = 0; i < V; i++) {
        cout << i << " : ";
        for (int j = 0; j < V; j++)
            if (Matr[i][j] == 1)
                cout << "{" << i << "; " << j << "} ";
        cout << "\n";
    }
}

void Graph::dfs2(int a,int b, int L[],vector<vector<int>> &routes, vector<int> route) {
    L[a] = 1;
    route.push_back(a);
    if (a == b) {
        routes.push_back(route);
    } else {
        for (int i = 1; i < V; i++)
            if (Matr[a][i] == 1 && L[i] == -1)
                    dfs2(i, b, L, routes, route);
    }
    //route.pop_back();
    L[a] = -1;
}

int Graph::findRoute(int a, int b) {
    int *L;
    L = new int[V];
    for (int i = 1; i < V; i++) // заполняем список не посещенных вершин
        L[i] = -1;

    vector<vector<int>> routes;
    vector<int> route;
    dfs2(a, b, L, routes, route);

    for (int i = 0; i < routes.size(); i++) {
        for (int j = 0; j < routes[i].size(); j++) {
            cout << routes[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

int Graph::findMaxRoute() {
    int *L;
    int res;
    L = new int[V];
    for (int i = 1; i < V; i++) // заполняем список не посещенных вершин
        L[i] = -1;

    vector<int> route;
    int route_index = 0;
    //dfs2(a,b,L,route,route_index);
    /*for (int v = 1; v < V; v++) {
        cout << v;
        vector<vector<int>> routes = dfs2(v, route, -1);
        for (int i = 0; i < routes.size(); i++) {
            for (int j = 0; j < routes[i].size(); j++) {
                cout << routes[i][j] << " ";
            }
            cout << endl;
        }
    }*/
    return 0;
}


Edge::Edge(int v, int w) {
    this->v = v;
    this->w = w;
}
