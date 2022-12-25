#include <vector>
#include <map>
#include <queue>
#include <iostream>
#include <limits>

#include "vertices.h"

using namespace std;

//TODO: refactor and fix params

typedef pair<int, int> pair_entry;

const int NV = 27;
const int start_node = 22;
const int target_node = 5;
const int INF = numeric_limits<int>::max();


struct graph {
    vector<vector<int>> adjacency_list;
    map<int, string> cities = {{0, vertices[0]}};
    vector<int> dfs_prev;
    vector<int> dls_prev;
    vector<int> ids_prev;
};


//struct inf_path {
//    vector<int> distances;
//    int length;
//};

struct weight_graph {
    bool is_bfs_heuristic = false;
    vector<int> distances;
    vector<vector<pair_entry>> adj_weight_list;
    map<int, string> nodes = {{0, vertices[0]}};
};

void print_map(map<string, int> &m) {
    for (auto [key, value] : m) {
        cout << '[' << key << "] = " << value << "; ";
        cout << endl;
    }
}

void fill_adjacency_list(struct graph* gr) {
    map<string, int> vg = { {vertices[0], 0} };
    for (int i = 1; i < vertices.size(); i++) {
        if (!vg.contains(vertices[i])) vg[vertices[i]] = vg.size();
    }
    for (auto [key, value]: vg) {
        gr->cities[value] = key;
    }
//    print_map(vg);
    gr->adjacency_list.resize(NV);
    for (auto & edge : graph_list) {
        int begin = vg[edge[0]];
        int end = vg[edge[1]];
        gr->adjacency_list[begin].push_back(end);
        gr->adjacency_list[end].push_back(begin);
    }
}

void print_adjacency_list(struct graph* gr) {
    for (int j = 0; j < gr->adjacency_list.size(); j++) {
        cout << j << " vertice: ";
        for (int l : gr->adjacency_list[j]) {
            cout << l << ' ';
        }
        cout << endl;
    }
}


void bfs(struct graph* gr) {
    cout << "---BFS---" << endl;
    int node = start_node;
    queue<int> q;
    vector<bool> used(NV, false);
    vector<int> dist(NV);
    vector<int> prev(NV);

    used[node] = true;
    prev[node] = -1;
    dist[node] = 0;
    q.push(node);

    while (!q.empty()) {
        node = q.front();
//        if (node == target_node) {
//            cout << "target node ";
//            cout << gr->cities.find(node)->second << ", dist = " << dist[node];
//            cout << endl;
//            break;
//        }
        q.pop();

        for (int& v: gr->adjacency_list[node]) {
            if (!used[v]) {
                used[v] = true;
                dist[v] = dist[node] + 1;
                prev[v] = node;
                q.push(v);
            }
        }
    }
}


int depth = 0;
int shortest_depth = INT32_MAX;
vector<int> visited(NV);
void dfs(int node, int t, struct graph* g) {
    depth++;
    if (depth > shortest_depth) return;

    if (node == t) {
        shortest_depth = depth;
        return;
    }

    visited[node] = true;
    vector<vector<int>> adj_list = g->adjacency_list;
    vector<int> adj_v = adj_list[node];
    for (int &v: adj_v) {
        if (!visited[v]) {
            g->dfs_prev[v] = node;
            dfs(v, t, g);
        }
    }
    depth--;
}

void print_dfs(struct graph* gr) {
    vector<int> verts;
    int vertex = target_node;
    while (vertex!=-1) {
        verts.push_back(vertex);
        vertex = gr->dfs_prev[vertex];
    }
    std::reverse(verts.begin(), verts.end());
    for (int v: verts) {
        cout << gr->cities.find(v)->second << ' ';
    }
    cout << endl;
    cout << "dist = " << verts.size() - 1 << endl;
}

void start_dfs(struct graph* gr) {
    cout << "---DFS---" << endl;
    gr->dfs_prev.resize(NV);
    gr->dfs_prev[start_node] = -1;
    dfs(start_node, target_node, gr);
    print_dfs(gr);
}

int get_intersection(const bool *s_used, const bool *t_used) {
    for (int i = 0; i < NV; i++) {
        if (s_used[i] && t_used[i])
            return i;
    }
    return -1;
}

void BFS(queue<int> &v_queue, bool *visited, int *parent, struct graph *gr) {
    int node = v_queue.front();
    v_queue.pop();
    vector<vector<int>> adj_list = gr->adjacency_list;
    for (int &v: adj_list[node]) {
        if (!visited[v]) {
            parent[v] = node;
            visited[v] = true;
            v_queue.push(v);
        }
    }
}

void print_BS(const int *s_parent, const int *t_parent, int i_node, struct graph* g) {
    cout << "---BS---" << endl;
    vector<int> path;
    vector<int> dist;
    dist.resize(NV,0);
    path.push_back(i_node);
    int i = i_node;
    while (i!=start_node){
        int v = s_parent[i];
        path.push_back(v);
        i = v;
    }
    reverse(path.begin(), path.end());
    i = i_node;
    while (i!=target_node) {
        int v = t_parent[i];
        path.push_back(v);
        i = v;
    }
    for (int v: path) {
        cout << g->cities.find(v)->second << ' ';
    }
    cout << endl;
    cout << "dist = " << path.size() - 1 << endl;
}

void BS(struct graph* gr) {
    bool s_used[NV], t_used[NV];
    int s_parent[NV], t_parent[NV];
    queue<int> s_queue, t_queue;

    for (int i = 0; i < NV; i++) {
        s_used[i] = false;
        t_used[i] = false;
    }

    s_queue.push(start_node);
    s_used[start_node] = true;
    s_parent[start_node] = -1;
    t_queue.push(target_node);
    t_used[target_node] = true;
    t_parent[target_node] = -1;

    while (!s_queue.empty() && !t_queue.empty()) {
        BFS(s_queue, s_used, s_parent, gr);
        BFS(t_queue, t_used, t_parent, gr);
    }
    int i_node = get_intersection(s_used, t_used);
    if (i_node != -1) {
//        cout << "i_node: " << i_node;
        print_BS(s_parent, t_parent, i_node, gr);
    }
}

int dls_depth = 0;
int depth_limit = 6;
vector<int> dls_visited(NV);
void dls(int node, int t, struct graph* gr) {
    dls_depth++;
    if (dls_depth > depth_limit) return;
    dls_visited[node] = true;
    vector<vector<int>> adj_list = gr->adjacency_list;
    vector<int> adj_v = adj_list[node];
    for (int &v: adj_v) {
        if (!dls_visited[v]) {
            depth++;
            gr->dls_prev[v] = node;
            dls(v, t, gr);
        }
    }
    dls_depth--;
}

void print_dls(struct graph* g) {
    cout << "---DLS---" << endl;
    vector<int> dls_vertices;
    int vertex = target_node;
    while (vertex!=-1) {
        dls_vertices.push_back(vertex);
        vertex = g->dls_prev[vertex];
    }
    std::reverse(dls_vertices.begin(), dls_vertices.end());
    for (int v: dls_vertices) {
        cout << g->cities.find(v)->second << ' ';
    }
    cout << endl;
    cout << "dist = " << dls_vertices.size() - 1 << endl;
}

void start_dls(struct graph* gr) {
    gr->dls_prev.resize(NV);
    gr->dls_prev[start_node] = -1;
    dls(start_node, target_node, gr);
    print_dls(gr);
}

bool ids_dls(int s, int t, int d, struct graph* gr) {
    if (s==t) return true;
    if (d <= 0) return false;
    vector<vector<int>> adj_l = gr->adjacency_list;
    vector<int> adj_v = adj_l[s];
    for (int &v: adj_v) {
        if (ids_dls(v,t,d-1, gr)) {
            gr->ids_prev[v] = s;
            return true;
        }
    }
    return false;
}

bool ids(int s, int t, struct graph* gr) {
    cout << "---IDS---" << endl;
    for (int i = 0; i <= depth_limit; i++) {
        if (ids_dls(s,t,i, gr)) return  true;
    }
    return false;
}

void print_ids(struct graph* gr) {
    vector<int> ids_v;
    int vertex = target_node;
    while (vertex!=-1) {
        ids_v.push_back(vertex);
        vertex = gr->ids_prev[vertex];
    }
    std::reverse(ids_v.begin(), ids_v.end());
    for (int v: ids_v) {
        cout << gr->cities.find(v)->second << ' ';
    }
    cout << endl;
    cout << "dist = " << ids_v.size() - 1 << endl;
}

void start_ids (struct graph* gr) {
    gr->ids_prev.resize(NV);
    gr->ids_prev[start_node] = -1;
    if (ids(start_node,target_node, gr)) {
        cout << "A path with a given depth was found" << endl;
        print_ids(gr);
    } else cout << "A path with a given depth wasn't found" << endl;
}

struct estimate {
    vector<int> weights;
    vector<int> distances;
};

void fill_weight_graph(struct weight_graph* wg_ref, struct estimate* est) {
    map<string, int> vg = { {vertices[0], 0} };
    for (int i = 1; i < vertices.size(); i++) {
        if (!vg.contains(vertices[i])) vg[vertices[i]] = vg.size();
    }
    for (auto [key, value]: vg) {
        wg_ref->nodes[value] = key;
    }
    wg_ref->adj_weight_list.resize(NV);
    for (auto & edge: edges_weights_list) {
        int begin = vg[edge[0]];
        int end = vg[edge[1]];
        int weight = stoi(edge[2]);
        if (wg_ref->is_bfs_heuristic) {
            wg_ref->adj_weight_list[begin].emplace_back(weight, end);
            wg_ref->adj_weight_list[end].emplace_back(weight, begin);
        } else {
            int h1 = est->distances[end];
            int h2 = est->distances[begin];
            wg_ref->adj_weight_list[begin].emplace_back(weight+h1, end);
            wg_ref->adj_weight_list[end].emplace_back(weight+h2,begin);
        }
    }
}

void greedy_bfs(struct weight_graph* wg_ref, struct estimate* est) {
    cout << "---Greedy BFS---" << endl;
    vector<int> distances(NV, INF);
    vector<int> prev(NV);
    priority_queue<pair_entry , vector<pair_entry>, greater<>> pq;

    distances[start_node] = 0;
    est->distances[start_node] = 0;

    prev[start_node] = -1;
    pq.emplace(0,start_node);
    while(!pq.empty()) {
        pair_entry wv = pq.top();
        int node = wv.second, cur_weight = wv.first;
        pq.pop();
        if (node == target_node) break;
        if (cur_weight > distances[node]) continue;
        vector<pair_entry> adj_vertices = wg_ref->adj_weight_list[node];
        for (auto vw: adj_vertices) {
            if (distances[vw.second] > distances[node] + vw.first) {
                prev[vw.second] = node;
                distances[vw.second] = distances[node] + vw.first;
                est->distances[vw.second] = distances[vw.second];
                pq.emplace(vw.first, vw.second);
            }
        }
    }
    cout << "distance: " << distances[target_node] << endl;

    vector<int> path;
    int point = target_node;
    while(prev[point] != -1) {
        path.push_back(point);
        point = prev[point];
    }
    reverse(path.begin(), path.end());
    cout << "path: ";
    for (auto v: path) {
        cout << wg_ref->nodes.find(v)->second << '-';
    }
    cout << endl;
}

void A_star(struct weight_graph* wg_ref, struct estimate* est) {
    vector<int> heuristics(NV, INF);
    vector<int> distances(NV, INF);
    vector<int> prev(NV);
    priority_queue<pair_entry , vector<pair_entry>, greater<>> pq;

    heuristics[start_node] = 0;
    distances[start_node] = 0;
    prev[start_node] = -1;
    pq.emplace(0,start_node);
    while(!pq.empty()) {
        pair_entry wv = pq.top();
        int node = wv.second, cur_heur = wv.first;
        pq.pop();
        if (node == target_node) break;
        if (cur_heur > heuristics[node]) continue;
        vector<pair_entry> adj_vertices = wg_ref->adj_weight_list[node];
        for (auto vw: adj_vertices) {
            if (heuristics[vw.second] > heuristics[node] + vw.first) {
                prev[vw.second] = node;
                heuristics[vw.second] = heuristics[node] + vw.first;
                pq.emplace(vw.first, vw.second);
            }
        }
    }
    cout << "distance: " << est->distances[target_node] << endl;

    vector<int> path;
    int point = target_node;
    while(prev[point] != -1) {
        path.push_back(point);
        point = prev[point];
    }
    reverse(path.begin(), path.end());
    cout << "path: ";
    for (auto v: path) {
        cout << wg_ref->nodes.find(v)->second << '-';
    }
    cout << endl;
}

void start_inf_searches() {
    weight_graph dijkstra;
    weight_graph astar;
    estimate estimate;
    dijkstra.distances.resize(NV);
    astar.distances.resize(NV);
    estimate.distances.resize(NV);
    dijkstra.is_bfs_heuristic = true;
    fill_weight_graph(&dijkstra, &estimate);
    greedy_bfs(&dijkstra, &estimate);

    fill_weight_graph(&astar, &estimate);
    A_star(&astar, &estimate);
}

void start_base_searches() {
    graph gr;
    fill_adjacency_list(&gr);
    bfs(&gr);
    start_dfs(&gr);
    BS(&gr);
    start_dls(&gr);
    start_ids(&gr);
}