//
// Created by 0ilya on 04.12.2022.
//

#include "Graph.cpp"

int main() {
    int N = 6;
    //cout << "Enter the number of edges: ";
    //cin >> N;
    Graph graph(N);
    /*for (int i = 0; i < N; i++) {
        int v1, w1;
        cout << "Enter the first vertex of the edge: " << endl;
        cin >> v1;
        cout << "Enter the second vertex of the edge: " << endl;
        cin >> w1;
        Edge newEdge = Edge(v1, w1);
        graph.addEdge(newEdge);
    }*/
    Edge e;

    e.v=1;e.w=2;graph.addEdge(e);
    e.v=1;e.w=3;graph.addEdge(e);
    e.v=2;e.w=4;graph.addEdge(e);
    e.v=2;e.w=5;graph.addEdge(e);
    e.v=3;e.w=4;graph.addEdge(e);
    e.v=3;e.w=6;graph.addEdge(e);
    e.v=3;e.w=2;graph.addEdge(e);
    e.v=4;e.w=5;graph.addEdge(e);
    e.v=4;e.w=6;graph.addEdge(e);
    e.v=5;e.w=6;graph.addEdge(e);

    graph.printGraph();
    graph.printGraphList();

    int root = graph.findRoot();
    cout << "The root: " << root << endl;
    int maxRouteLength = graph.findMaxRoute();
    cout << "The max route length: " << maxRouteLength << endl;
    graph.shortestPath(1, 6);

    return 0;
}







/*
 * my test graph:
 *  e.v=2;e.w=7;graph.addEdge(e);
    e.v=7;e.w=6;graph.addEdge(e);
    e.v=2;e.w=3;graph.addEdge(e);
    e.v=6;e.w=5;graph.addEdge(e);
    e.v=6;e.w=8;graph.addEdge(e);
    e.v=3;e.w=1;graph.addEdge(e);
    e.v=3;e.w=9;graph.addEdge(e);
    e.v=9;e.w=4;graph.addEdge(e);
    e.v=1;e.w=10;graph.addEdge(e);
    e.v=10;e.w=11;graph.addEdge(e);
    e.v=3;e.w=8;graph.addEdge(e);
   // e.v=3;e.w=10;graph.addEdge(e);
 */

/*
 * graph 5:
    e.v=1;e.w=2;graph.addEdge(e);
    e.v=1;e.w=3;graph.addEdge(e);
    e.v=1;e.w=4;graph.addEdge(e);
    e.v=4;e.w=6;graph.addEdge(e);
    e.v=2;e.w=5;graph.addEdge(e);
    e.v=2;e.w=4;graph.addEdge(e);
    e.v=5;e.w=6;graph.addEdge(e);
    e.v=4;e.w=5;graph.addEdge(e);
    e.v=3;e.w=6;graph.addEdge(e);
 */
/*
 *  graph 6
    e.v=1;e.w=2;graph.addEdge(e);
    e.v=1;e.w=3;graph.addEdge(e);
    e.v=2;e.w=4;graph.addEdge(e);
    e.v=2;e.w=5;graph.addEdge(e);
    e.v=3;e.w=4;graph.addEdge(e);
    e.v=3;e.w=6;graph.addEdge(e);
    e.v=3;e.w=2;graph.addEdge(e);
    e.v=4;e.w=5;graph.addEdge(e);
    e.v=4;e.w=6;graph.addEdge(e);
    e.v=5;e.w=6;graph.addEdge(e);
 */