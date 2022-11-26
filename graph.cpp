
#include <iostream>
#include <queue>
#include <map>
#include "graph.h"


graph::graph(vector<string> str_vertices_list) {
    nv = 27;
    this->str_vertices_list=std::move(str_vertices_list);
    adjacency_list.resize(nv);
}

void print_map(map<string, int> &m) {
    for (auto [key, value] : m) {
        cout << '[' << key << "] = " << value << "; ";
        cout << endl;
    }
}

void graph::print_adj_list() {
    for (int j = 0; j < adjacency_list.size(); j++) {
        cout << j << " vertice: ";
        for (int l : adjacency_list[j]) {
            cout << l << ' ';
        }
        cout << endl;
    }
}

map<string,int> get_indexing_map(vector<string> g) {
    map<string, int> vg = { {g[0], 0} };
    for (int i = 1; i < g.size(); i++) {
        if (!vg.contains(g[i])) vg[g[i]] = vg.size();
    }
    return vg;
}


void graph::fillAdjacencyList(vector<vector<string>> edges) {
    map<string, int> vg = get_indexing_map(str_vertices_list);
//    print_map(vg);
    for (auto & edge : edges) {
        int begin = vg[edge[0]];
        int end = vg[edge[1]];
        adjacency_list[begin].push_back(end);
        adjacency_list[end].push_back(begin);
    }
}

int graph::getNv() const {
    return nv;
}

int graph::getS() const {
    return s;
}

int graph::getT() const {
    return t;
}

const vector<vector<int>> &graph::getAdjacencyList() const {
    return adjacency_list;
}




