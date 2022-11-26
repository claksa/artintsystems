#ifndef LAB2_PATH_H
#define LAB2_PATH_H

#include "graph.h"

class path {

protected:
    bool* visited;
    graph g;
    int vertices;

public:
    explicit path(const graph& gr);

};

class bfs : public path {
public:
    explicit bfs(const graph &gr);
    void search();
};

class dfs: public path {
    int depth = 0;
    int shortest_depth = INT32_MAX;
    int *prev;

private:
    void search(int, int);
    void print_dfs(int);
public:
    explicit dfs(const graph &gr);
    void init_search();
};

class bs: public path {
private:
    int get_intersection(const bool *, const bool *) ;
    void print_BS(const int *s_parent, const int *t_parent, int i_node);
    void BFS(queue<int> &v_queue, bool *visited, int *parent);
public:
    explicit bs(const graph &gr);
    void search();
};

class dls: public path {
private:
    int depth_limit = 5;
    int *prev;
    int depth = 0;
    void search(int, int);
    void print_dls(int);
public:
    explicit dls(const graph &gr);
    void init_search();
};
#endif //LAB2_PATH_H
