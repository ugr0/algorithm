#include <bits/stdc++.h>
using namespace std;

const long long INF = 1LL << 60;

struct Edge {
  int to;
  long long w;
  Edge(int to, long long w) : to(to), w(w) {}
};

using Graph = vector<vector<Edge>>;

template <class T>
bool chmin(T& a, T b) {
  if (a > b) {
    a = b;
    return true;
  } else
    return false;
}

int main() {
  int N, M, s;
  cin >> N >> M >> s;

  Graph G(N);
  for (int i = 0; i < M; i++) {
    int a, b, w;
    cin >> a >> b >> w;
    G[a].push_back(Edge(b, w));
  }

  // dijkstra
  vector<long long> dist(N, INF);
  dist[s] = 0;

  // (d[v], v)のペアを要素としたヒープを作る
  priority_queue<pair<long long, int>, vector<pair<long long, int>>,
                 greater<pair<long long, int>>>
      que;

  que.push(make_pair(dist[s], s));

  // ダイクストラ法の反復を開始
  while (!que.empty()) {
    // v: 使用済みでない頂点のうちd[v]が最小の頂点
    // d: vに対するキー値
    int v = que.top().second;
    long long d = que.top().first;
    que.pop();

    // d > dist[v]は(d, v)がゴミであることを意味する
    if (d > dist[v]) continue;

    // 頂点vを始点とした各辺を緩和
    for (auto e : G[v]) {
      if (chmin(dist[e.to], dist[v] + e.w)) {
        // 更新があるならヒープに新たに挿入
        que.push(make_pair(dist[e.to], e.to));
      }
    }
  }

  for (int v = 0; v < N; v++) {
    if (dist[v] < INF)
      cout << dist[v] << endl;
    else
      cout << "INF" << endl;
  }
}
