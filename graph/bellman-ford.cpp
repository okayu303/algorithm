#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <class T> bool chmin(T& a, T b) {
    if(a > b) { a = b; return true; }
    else return false;
}

constexpr int INF = 1 << 30;

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B&lang=ja
int main() {
    int n, m, s;
    cin >> n >> m >> s; // 頂点数、辺の数、始点

    // グラフの読み込み
    vector<vector<pair<int, int>>> g(n);  // 次の頂点、距離
    while(m--) {
        int a, b, d;
        cin >> a >> b >> d;
        g[a].emplace_back(b, d);    // 0-indexed
    }

    // ベルマン・フォード法
    // 負の辺を含むグラフの最短経路を求める。計算量はO(VE)
    vector<ll> dist(n, INF);   // 距離
    chmin(dist[s], 0ll);    // 距離の更新はchmin
    for(int itr = 0; itr < n; ++itr) {  // 負の閉路がなければ最大の更新回数はn回
        bool update = false;
        for(int v = 0; v < n; ++v) {
            if(dist[v] == INF) continue;   // 未訪問なのでスキップ
            for(auto e : g[v]) {    // 次の頂点、距離
                if(chmin(dist[e.first], dist[v] + e.second)) {  // 距離の更新はchmin
                    update = true;  // 更新あり
                }
            }
        }
        if(itr == n-1 && update) {  // 負の閉路が存在
            cout << "NEGATIVE CYCLE" << endl;
            return 0;
        }
        if(!update) break;
    }

    // 距離の出力
    for(auto i : dist) {
        if(i == INF) cout << "INF" << endl;
        else cout << i << endl;
    }
}