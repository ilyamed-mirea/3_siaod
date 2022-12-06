//
// Created by 0ilya on 04.12.2022.
//

#ifndef INC_3_SIAOD_GRAPH_H
#define INC_3_SIAOD_GRAPH_H

//ребро
struct Edge {
    int v; //from
    int w; //to
    Edge(int v,int w);
};

struct Graph {
    int V; // количество вершин
    int E; // количество ребер
    int **Matr; // матрица смежности

    Graph(int N);

    void addEdge(Edge edge);

    void removeEdge(Edge edge);

    void printGraph();

    void printGraphList();

    void dfs(int v, int *&L); //обход в глубину - Depth First Search
    int findRoot();

    int findRoute(int a, int b);

    int findMaxRoute();

    ~Graph();
    void dfs2(int a,int b, int L[],std::vector<std::vector<int>> &routes, std::vector<int> route);

   // std::vector<std::vector<int>> dfs2(int v, std::vector<int> &routes, int ind);
};

#endif //INC_3_SIAOD_GRAPH_H
