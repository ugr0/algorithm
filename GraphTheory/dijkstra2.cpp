/*
    ei1333さんのやつ
*/

#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0; i<(n); ++i)
using ll = long long;
using pll = pair<ll,ll>;
const ll INF64 = 1LL << 60;
const int INF = (1 << 29);

// graph template----------------------------------------------------------
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

// dijkstra-----------------------------------------------------------
template< typename T >
struct ShortestPath {
    vector< T > dist;
    vector< int > from, id;
};

template< typename T >
ShortestPath< T > dijkstra(const Graph< T > &g, int s) {
    const auto INF = numeric_limits< T >::max();
    vector< T > dist(g.size(), INF);
    vector< int > from(g.size(), -1), id(g.size(), -1);
    using Pi = pair< T, int >;
    priority_queue< Pi, vector< Pi >, greater<> > que;
    dist[s] = 0;
    que.emplace(dist[s], s);
    while(!que.empty()) {
        T cost;
        int idx;
        tie(cost, idx) = que.top();
        que.pop();
        if(dist[idx] < cost) continue;
        for(auto &e : g.g[idx]) {
        auto next_cost = cost + e.cost;
        if(dist[e.to] <= next_cost) continue;
        dist[e.to] = next_cost;
        from[e.to] = idx;
        id[e.to] = e.idx;
        que.emplace(dist[e.to], e.to);
        }
    }
    return {dist, from, id};
}

int main(){
    int V, E, r;
    cin >> V >> E >> r;
    Graph<int> g(V);
    g.read(E, 0, true, true);
    for(auto &dist : dijkstra(g, r).dist){
        if(dist == numeric_limits<int>::max()) cout << "INF" << endl;
        else cout << dist << endl;
    }
}