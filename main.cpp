
#include <clocale>
#include <iostream>
#include "vertices.h"
#include "graph.h"
#include "path.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "");
    graph graph(vertices);
    graph.fill_adjacency_list(graph_list);
    graph.fill_adj_weight_list(edges_weights_list);
    inf_bfs bfs(graph);
    bfs.search();
//    graph.print_adj_list();
//    graph.BFS(start_node, end_node);
//    if (graph.BS(start_node,end_node) == -1) {
//        cout << "fail" << endl;
//    }
    return 0;
}
