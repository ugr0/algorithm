/*
    ei1333さんのやつ
    クラスカル 𝑂(|𝐸|log|𝑉|)
    最小全域木
    https://algo-logic.info/kruskal-mst/
    https://onlinejudge.u-aizu.ac.jp/solutions/problem/GRL_2_A/review/3594572/beet/C++14
*/

#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0; i<(n); ++i)
using ll = long long;
using pll = pair<ll,ll>;
const ll INF64 = 1LL << 60;
const int INF = (1 << 29);

//graph template---------------------------------------------------
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

//kruskal-mst--------------------------------------
struct UnionFind {
    vector< int > data;

    UnionFind() = default;

    explicit UnionFind(size_t sz) : data(sz, -1) {}

    bool unite(int x, int y) {
        x = find(x), y = find(y);
        if(x == y) return false;
        if(data[x] > data[y]) swap(x, y);
        data[x] += data[y];
        data[y] = x;
        return true;
    }

    int find(int k) {
        if(data[k] < 0) return (k);
        return data[k] = find(data[k]);
    }

    int size(int k) {
        return -data[find(k)];
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }
};

template< typename T >
struct MinimumSpanningTree {
    T cost;
    Edges< T > edges;
};

template< typename T >
MinimumSpanningTree< T > kruskal(Edges< T > &edges, int V) {
    sort(begin(edges), end(edges), [](const Edge< T > &a, const Edge< T > &b) {
        return a.cost < b.cost;
    });
    UnionFind tree(V);
    T total = T();
    Edges< T > es;
    for(auto &e : edges) {
        if(tree.unite(e.from, e.to)) {
        es.emplace_back(e);
        total += e.cost;
        }
    }
    return {total, es};
}

int main(){
    int V,E; cin >> V >> E;
    Edges<int> edges;
    for(int i=0; i<E; i++){
        int a,b,c; cin >> a >> b >> c;
        edges.emplace_back(a,b,c);
    }

    cout << kruskal(edges, V).cost << endl;
}