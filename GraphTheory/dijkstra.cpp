//
// dijkstra O(E log(V))
// https://atcoder.jp/contests/joi2008yo/tasks/joi2008yo_f
//

#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0; i<(n); ++i)
using ll = long long;
using pll = pair<ll,ll>;
const ll INF = (1LL << 60);

struct Edge{ll to, cost;};
struct Graph{
    ll V;
    vector<vector<Edge> > G;
    vector<ll> d;

    Graph(ll n){
        init(n);
    }

    void init(ll n){
        V = n;
        G.resize(V);
        d.resize(V);
        rep(i,V){
        d[i] = INF;
        }
    }

    void add_edge(ll s, ll t, ll cost){
        Edge e;
        e.to = t, e.cost = cost;
        G[s].push_back(e);
    }

    void dijkstra(ll s){
        rep(i,V) d[i] = INF;
        d[s] = 0;
        priority_queue<pll,vector<pll>, greater<pll> > que;
        que.push(pll(0,s));
        while(!que.empty()){
            pll p = que.top(); que.pop();
            ll v = p.second;
            if(d[v]<p.first) continue;
            for(auto e : G[v]){
                if(d[e.to]>d[v]+e.cost){
                    d[e.to] = d[v]+e.cost;
                    que.push(pll(d[e.to],e.to));
                }
            }
        }
    }
};

/********** Main()  function **********/
int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);

    int n, k; cin >> n >> k;
    //n頂点のグラフを作成
    Graph g(n);

    rep(i,k){
        int x; cin >> x;
        if(x==0){
            int a,b; cin >> a >> b;
            a--,b--;
            //頂点aからの各頂点への単一視点最短距離を探索できる
            g.dijkstra(a);

            //g.d[i]でaから頂点iへの最短距離が計算される
            //もし経路がないならINFが返る
            if(g.d[b]==INF) cout << -1 << endl;
            else cout << g.d[b] << endl;
        }else{
            int c,d,e; cin >> c >> d >> e;
            c--,d--;
            //g.add_edge(a,b,cost)..aからbにコストcostの辺が張られる
            g.add_edge(c,d,e);
            g.add_edge(d,c,e);
        }
    }

}
/********  Main() Ends Here *************/
