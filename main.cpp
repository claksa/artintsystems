
#include <clocale>
#include <iostream>
#include "vertices.h"
#include "graph.h"
#include "path.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "");
    graph graph(vertices);
    graph.fillAdjacencyList(graph_list);
    dls dfs(graph);
    dfs.init_search();
//    graph.print_adj_list();
//    graph.BFS(start_node, end_node);
//    if (graph.BS(start_node,end_node) == -1) {
//        cout << "fail" << endl;
//    }
    return 0;
}
