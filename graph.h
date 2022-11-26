#ifndef LAB2_GRAPH_H
#define LAB2_GRAPH_H

#include <vector>
#include <string>
#include <queue>

using namespace std;

class graph {

    int nv;
    int s = 22;
    int t = 5;
    vector<vector<int>> adjacency_list;
    vector<string> str_vertices_list;

//    vector<vector<string>> edges;

public:

    explicit graph(vector<string> str_vertices_list);
    void fillAdjacencyList(vector<vector<string>> edges);
    void print_adj_list();

    int getNv() const;
    int getT() const;
    int getS() const;
    const vector<vector<int>> &getAdjacencyList() const;
};




#endif //LAB2_GRAPH_H
