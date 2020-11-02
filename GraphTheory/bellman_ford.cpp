/*
    ei1333さんのやつ
    https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_B
    https://algo-logic.info/bellman-ford/
    負の辺が含まれているような場合でも適用可能
    負の閉路がグラフに含まれている際はそれを検出することができる
    O(|V|*|E|)
*/

#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0; i<(n); ++i
using ll = long long;

template< typename T = int >
struct Edge {
    int from, to;
    T cost;
    int idx;

    Edge() = default;

    Edge(int from, int to, T cost = 1, int idx = -1) : from(from), to(to), cost(cost), idx(idx) {}

    operator int() const { return to; }
};

template< typename T = int >
struct Graph {
    vector< vector< Edge< T > > > g;
    int es;

    Graph() = default;

    explicit Graph(int n) : g(n), es(0) {}

    size_t size() const {
        return g.size();
    }

    void add_directed_edge(int from, int to, T cost = 1) {
        g[from].emplace_back(from, to, cost, es++);
    }

    void add_edge(int from, int to, T cost = 1) {
        g[from].emplace_back(from, to, cost, es);
        g[to].emplace_back(to, from, cost, es++);
    }

    void read(int M, int padding = -1, bool weighted = false, bool directed = false) {
        for(int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        a += padding;
        b += padding;
        T c = T(1);
        if(weighted) cin >> c;
        if(directed) add_directed_edge(a, b, c);
        else add_edge(a, b, c);
        }
    }
};

template< typename T >
using Edges = vector< Edge< T > >;
template< typename T >
using WeightedGraph = vector< Edges< T > >;
using UnWeightedGraph = vector< vector< int > >;
template< typename T >
using Matrix = vector< vector< T > >;

template< typename T >
vector< T > bellman_ford(const Edges< T > &edges, int V, int s) {
    const auto INF = numeric_limits< T >::max();
    vector< T > dist(V, INF);
    dist[s] = 0;
    for(int i = 0; i < V - 1; i++) {
        for(auto &e : edges) {
        if(dist[e.from] == INF) continue;
        dist[e.to] = min(dist[e.to], dist[e.from] + e.cost);
        }
    }
    for(auto &e : edges) {
        if(dist[e.from] == INF) continue;
        if(dist[e.from] + e.cost < dist[e.to]) return vector< T >();
    }
    return dist;
}

int main(){
    int V, E, R;
    cin >> V >> E >> R;
    Edges<int> es;
    for(int i = 0; i < E; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        es.emplace_back(a, b, c);
    }
    auto dists = bellman_ford(es, V, R);
    if(dists.empty()) cout << "NEGATIVE CYCLE\n";
    for(auto &dist : dists) {
        if(dist == numeric_limits< int >::max()) cout << "INF\n";
        else cout << dist << "\n";
    }
}