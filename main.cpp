
#include <clocale>
#include <iostream>
#include "vertices.h"
#include "graph.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "");
    int vertices_num = 27;
    int start_node = 22;
    int end_node = 5;
    graph graph(vertices_num,vertices);
    graph.fillAdjacencyList(graph_list);
//    graph.print_adj_list();
//    graph.BFS(start_node, end_node);
//    if (graph.BS(start_node,end_node) == -1) {
//        cout << "fail" << endl;
//    }
    graph.init_DFS();
    return 0;
}
