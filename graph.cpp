
#include <iostream>
#include <queue>
#include <map>
#include <utility>
#include "graph.h"


graph::graph(int nv, vector<string> str_vertices_list) {
    this->nv=nv;
    this->str_vertices_list=std::move(str_vertices_list);
    adjacency_list.resize(nv);
}

void graph::BFS(int node, int end_node) {
    queue<int> q;
    vector<bool> used;
    vector<int> dist;
    used.resize(nv, false);
    dist.resize(nv, 0);

    used[node] = true;
    q.push(node);

    while (!q.empty()) {
        node = q.front();
        if (node == end_node) {
            cout << node << ", dist = " << dist[node];
            cout << endl;
            break;
        }
        q.pop();

        for (int& v: adjacency_list[node]) {
            if (!used[v]) {
                used[v] = true;
                dist[v] = dist[node] + 1;
                q.push(v);
            }
        }
    }
}


void graph::BFS(queue<int> &v_queue, bool *used, int *parent) {
    int node = v_queue.front();
    v_queue.pop();
    for (int &v: adjacency_list[node]) {
        if (!used[v]) {
            parent[v] = node;
            used[v] = true;
            v_queue.push(v);
        }
    }
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

int graph::get_intersection(const bool *s_used, const bool *t_used) const {
    for (int i = 0; i < nv; i++) {
        if (s_used[i] && t_used[i])
            return i;
    }
    return -1;
}

void graph::print_BS(int *s_parent, int *t_parent, int i_node, int s, int t) {
    vector<int> path;
    vector<int> dist;
    dist.resize(nv,0);
    path.push_back(i_node);
    int i = i_node;
    while (i!=s){
        int v = s_parent[i];
        path.push_back(v);
        i = v;
    }
    reverse(path.begin(), path.end());
    i = i_node;
    while (i!=t) {
        int v = t_parent[i];
        path.push_back(v);
        i = v;
    }
    cout << "--path--" << endl;
    for (int v: path) {
        cout << v << ' ';
    }
    cout << endl;
    cout << "dist = " << path.size() - 1 << endl;
}


int graph::BS(int s, int t) {
    bool s_used[nv], t_used[nv];
    int s_parent[nv], t_parent[nv];
    queue<int> s_queue, t_queue;

    for (int i = 0; i < nv; i++) {
        s_used[i] = false;
        t_used[i] = false;
    }

    s_queue.push(s);
    s_used[s] = true;
    s_parent[s] = -1;
    t_queue.push(t);
    t_used[t] = true;
    t_parent[t] = -1;

    while (!s_queue.empty() && !t_queue.empty()) {
        BFS(s_queue, s_used, s_parent);
        BFS(t_queue, t_used, t_parent);
    }
    int i_node = get_intersection(s_used, t_used);
    if (i_node != -1) {
        cout << "i_node: " << i_node;
        print_BS(s_parent, t_parent, i_node, s, t);
    }

    return 0;
}







