//
// Created by 0ilya on 04.12.2022.
//

#ifndef INC_3_SIAOD_GRAPH_H
#define INC_3_SIAOD_GRAPH_H

//ребро
struct Edge {
    int v; //from
    int w; //to
    Edge(int v = 0, int w = 0);
};

struct Graph {
    int V; // количество вершин
    int E; // количество ребер
    int **Matr; // матрица смежности

    Graph(int N = 10);

    void addEdge(Edge edge);

    void removeEdge(Edge edge);

    void printGraph();

    void printGraphList();

    void dfs(int v, int *&L); //обход в глубину - Depth First Search

    int findRoot();

    void
    dfs2(int a, int b, std::vector<std::vector<int>> &routes, std::vector<int> route); // обход для нахождения путей

    std::vector<std::vector<int>> findAllRoutes(int a, int b);

    int findMaxRoute();

    void shortestPath(int a, int b);

    ~Graph();
};

#endif //INC_3_SIAOD_GRAPH_H
