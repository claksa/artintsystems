#ifndef LAB2_GRAPH_H
#define LAB2_GRAPH_H

#include <vector>
#include <string>
#include <queue>

using namespace std;

class graph {

    int nv;
    vector<vector<int>> adjacency_list;
    vector<string> str_vertices_list;
//    vector<vector<string>> edges;

public:

    graph(int nv, vector<string> str_vertices_list);

    void BFS(int, int);
    void BFS(queue<int> &v_queue, bool *used, int *parent);
    int get_intersection(const bool *, const bool *) const;
    void print_BS(int *s_parent, int *t_parent, int i_node, int s, int t);
    int BS(int, int);
    void fillAdjacencyList(vector<vector<string>> edges);
    void print_adj_list();

};




#endif //LAB2_GRAPH_H
