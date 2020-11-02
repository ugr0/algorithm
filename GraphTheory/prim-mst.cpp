/*
    プリム ei1333さんのやつ
    最小全域木 𝑂(|𝑉|2) ヒープを使わない場合
    https://algo-logic.info/prim-mst/
    https://onlinejudge.u-aizu.ac.jp/solutions/problem/GRL_2_A/review/3594572/beet/C++14
    https://ei1333.github.io/library/library/graph/mst/prim.cpp.html
*/

#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0; i<(n); ++i)
using ll = long long;
using pll = pair<ll,ll>;
const ll INF64 = 1LL << 60;
const int INF = (1 << 29);

//------------グラフテンプレート--------------
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

template< typename T = int >
using Edges = vector< Edge< T > >;

//--------------Prim-mst----------------
template< typename T >
struct MinimumSpanningTree {
    T cost;
    Edges< T > edges;
};

template< typename T >
MinimumSpanningTree< T > prim(const Graph< T > &g) {
    T total = T();
    vector< int > used(g.size());
    vector< Edge< T > * > dist(g.size());
    using pi = pair< T, int >;
    priority_queue< pi, vector< pi >, greater<> > que;
    que.emplace(T(), 0);
    Edges< T > edges;
    while(!que.empty()) {
        auto p = que.top();
        que.pop();
        if(used[p.second]) continue;
        used[p.second] = true;
        total += p.first;
        if(dist[p.second]) edges.emplace_back(*dist[p.second]);
        for(auto &e : g.g[p.second]) {
        if(used[e.to] || (dist[e.to] && dist[e.to]->cost <= e.cost)) continue;
        que.emplace(e.cost, e.to);
        }
    }
    return {total, edges};
}

int main(){
    int V, E;
    cin >> V >> E;
    Graph<> g(V);
    //g.read(辺の数, 差分(0-originなら-1), 重み付きならtrueに, 有向グラフならtrueに)
    g.read(E, 0, true);
    cout << prim(g).cost << endl;
}