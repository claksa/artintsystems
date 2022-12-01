#ifndef LAB2_GRAPH_H
#define LAB2_GRAPH_H

#include <vector>
#include <string>
#include <queue>

using namespace std;
typedef pair<int, int> vw;

class graph {

    int nv;
    int s = 22;
    int t = 5;
    vector<vector<int>> adjacency_list;
    vector<vector<vw>> adj_weight_list;
    vector<string> str_vertices_list;

//    vector<vector<string>> edges;

public:

    explicit graph(vector<string> str_vertices_list);
    void fill_adjacency_list(vector<vector<string>> edges);
    void fill_adj_weight_list(vector<vector<string>> edges);
    void print_adj_list();
    void print_adj_wlist();

    int getNv() const;
    int getT() const;
    int getS() const;
    const vector<vector<int>> &getAdjacencyList() const;

    const vector<vector<vw>> &getAdjWeightList() const;
};




#endif //LAB2_GRAPH_H
