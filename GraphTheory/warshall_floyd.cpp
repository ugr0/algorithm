/*
    ei1333さんのやつ
    https://ei1333.github.io/library/library/graph/template.cpp.html
*/

#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0; i<(n); ++i)
using ll = long long;
using pll = pair<ll,ll>;
const ll INF64 = 1LL<<60;
const int INF = (1 << 29);

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
template<typename T>
using Matrix = vector<vector< T >>;
template<typename T>
void warshall_floyd(Matrix< T > &g, T INF){
    for(int k = 0; k < g.size(); k++) {
        for(int i = 0; i < g.size(); i++) {
            for(int j = 0; j < g.size(); j++) {
                if(g[i][k] == INF || g[k][j] == INF) continue;
                g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
            }
        }
    }
}

int main(){
    int V,E;
    cin >> V >> E;
    Matrix<int> mat(V, vector<int>(V, INT_MAX));
    rep(i,V) mat[i][i] = 0;
    rep(i,E){
        int s,t,d; cin >> s >> t >> d;
        mat[s][t] = d;
    }
    warshall_floyd(mat, INT_MAX);
    rep(i,V){
        if(mat[i][i]<0){
            cout << "NEGATIVE CYCLE" << endl;
            return 0;
        }
    }
    rep(i,V){
        rep(j,V){
            if(j>0) cout << " ";
            if(mat[i][j]!=INT_MAX) cout << mat[i][j];
            else cout << "INF";
        }
        cout << endl;
    }
}