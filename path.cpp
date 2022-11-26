#include <iostream>
#include "path.h"


path::path(graph gr) : g(g) {
    this->g = gr;
    vertices = gr.getNv();
    visited = new bool[vertices];
}

bfs::bfs(const graph &gr) : path(gr) {}
bs::bs(const graph &gr) : path(gr) {}

dfs::dfs(const graph &gr) : path(gr) {
    prev = new int[vertices];
}

void bfs::search() {
    int s = g.getS();
    int t = g.getT();
    queue<int> q;
    vector<int> dist;
    dist.resize(vertices, 0);

    visited[s] = true;
    q.push(s);

    while (!q.empty()) {
        s = q.front();
        if (s == t) {
            cout << s << ", dist = " << dist[s];
            cout << endl;
            break;
        }
        q.pop();

        vector<vector<int>> adj_list = g.getAdjacencyList();
        for (int& v: adj_list[s]) {
            if (!visited[v]) {
                visited[v] = true;
                dist[v] = dist[s] + 1;
                q.push(v);
            }
        }
    }
}

void dfs::init_search() {
    int s = g.getS();
    int t = g.getT();
    prev[s] = -1;
    search(s, t);
    print_dfs(t);
}

void dfs::print_dfs(int t) {
    vector<int> vertices;
    int vertex = t;
    while (vertex!=-1) {
        vertices.push_back(vertex);
        vertex = prev[vertex];
    }
    std::reverse(vertices.begin(), vertices.end());
    for (int v: vertices) {
        cout << v << ' ';
    }
    cout << endl;
    cout << "dist = " << vertices.size() - 1 << endl;
}

void dfs::search(int node, int t) {
    depth++;
    if (depth > shortest_depth) return;

    if (node == t) {
        shortest_depth = depth;
        return;
    }

    visited[node] = true;
    vector<vector<int>> adj_list = g.getAdjacencyList();
    vector<int> adj_v = adj_list[node];
    for (int &v: adj_v) {
        if (!visited[v]) {
            prev[v] = node;
            search(v, t);
        }
    }
    depth--;
}

int bs::get_intersection(const bool *s_used, const bool *t_used) {
    for (int i = 0; i < vertices; i++) {
        if (s_used[i] && t_used[i])
            return i;
    }
    return -1;
}

void bs::search() {
    int s = g.getS();
    int t = g.getT();
    bool s_used[vertices], t_used[vertices];
    int s_parent[vertices], t_parent[vertices];
    queue<int> s_queue, t_queue;

    for (int i = 0; i < vertices; i++) {
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
        print_BS(s_parent, t_parent, i_node);
    }
}

void bs::print_BS(const int *s_parent, const int *t_parent, int i_node) {
    vector<int> path;
    vector<int> dist;
    dist.resize(vertices,0);
    path.push_back(i_node);
    int i = i_node;
    while (i!=g.getS()){
        int v = s_parent[i];
        path.push_back(v);
        i = v;
    }
    reverse(path.begin(), path.end());
    i = i_node;
    while (i!=g.getT()) {
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

void bs::BFS(queue<int> &v_queue, bool *visited, int *parent) {
    int node = v_queue.front();
    v_queue.pop();
    vector<vector<int>> adj_list = g.getAdjacencyList();
    for (int &v: adj_list[node]) {
        if (!visited[v]) {
            parent[v] = node;
            visited[v] = true;
            v_queue.push(v);
        }
    }
}
