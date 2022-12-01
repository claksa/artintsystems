#include <iostream>
#include "path.h"


path::path(const graph& gr) : g(gr), vertices(gr.getNv()){
    visited = new bool[vertices];
}

bfs::bfs(const graph &gr) : path(gr) {}
bs::bs(const graph &gr) : path(gr) {}
dls::dls(const graph &gr) : path(gr) {
    prev = new int[vertices];
}
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
    cout << "shortest depth = " << shortest_depth << endl;
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

void dls::search(int node, int t) {
    depth++;
    if (depth > depth_limit) return;
    visited[node] = true;
    vector<vector<int>> adj_list = g.getAdjacencyList();
    vector<int> adj_v = adj_list[node];
    for (int &v: adj_v) {
        if (!visited[v]) {
            depth++;
            prev[v] = node;
            search(v, t);
        }
    }
    depth--;
}

void dls::print_dls(int t) {
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

void dls::init_search() {
    int s = g.getS();
    int t = g.getT();
    prev[s] = -1;
    search(s, t);
    print_dls(t);
}

ids::ids(const graph &gr) : path(gr) {
    prev = new int[vertices];
}

bool ids::search(int s, int t) {
    for (int i = 0; i <= depth_limit; i++) {
        if (dls(s,t,i)) return  true;
    }
    return false;
}

bool ids::dls(int s, int t, int d) {
    if (s==t) return true;
    if (d <= 0) return false;
    vector<vector<int>> adj_l = g.getAdjacencyList();
    vector<int> adj_v = adj_l[s];
    for (int &v: adj_v) {
        if (dls(v,t,d-1)) {
            prev[v] = s;
            return true;
        }
    }
    return false;
}

void ids::print_ids(int t) {
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

void ids::init_search() {
    int s = g.getS();
    int t = g.getT();
    prev[s] = -1;
    if (search(s,t)) {
        cout << "A path with a given depth was found" << endl;
        print_ids(t);
    } else cout << "A path with a given depth wasn't found" << endl;
}

inf_bfs::inf_bfs(const graph &gr) : path(gr) {}

void inf_bfs::search() {
    int t = g.getT();
    int s = g.getS();
    int dist = 0;
    priority_queue<vw, vector<vw>, greater<>> pq;
    pq.push(make_pair(0,s));
    visited[s] = true;
    while(!pq.empty()) {
        int node = pq.top().second;
        cout << node << ' ';
//        cout << node << ", ";
//        cout << "weight: " << pq.top().first << endl;
        pq.pop();
        dist += pq.top().first;
        if (node == t) break;
        vector<vector<vw>> adj_wl = g.getAdjWeightList();
        vector<vw> adj_nodes = adj_wl[node];
        for (auto i: adj_nodes) {
            if (!visited[i.second]) {
                visited[i.second] = true;
                pq.push(make_pair(i.first,i.second));
            }
        }
    }
    cout << "distance: " << dist << endl;
}
