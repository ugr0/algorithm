//
// 与えられた無向グラフが２部グラフかどうか判定(BFS)
//

#include <iostream>
#include <vector>
#include <queue>
using namespace std;
using Graph = vector<vector<int>>;

int main() {
    // 頂点数と辺数
    int N, M; cin >> N >> M;

    // グラフ入力受取
    Graph G(N);
    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    bool is_bipartite = true;
    vector<int> dist(N, -1);
    queue<int> que;
    for (int v = 0; v < N; ++v) {
        if (dist[v] != -1) continue; // v が探索済みならスルー
        dist[v] = 0, que.push(v);
        while (!que.empty()) {
            int v = que.front(); que.pop();
            for (auto nv : G[v]) {
                if (dist[nv] == -1) {
                    dist[nv] = dist[v] + 1;
                    que.push(nv);
                } else {
                    // 整合性を確認する
                    if (dist[v] == dist[nv]) is_bipartite = false;
                }
            }
        }
    }

    if (is_bipartite) cout << "Yes" << endl;
    else cout << "No" << endl;
}