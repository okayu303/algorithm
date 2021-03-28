#include <bits/stdc++.h>
using namespace std;

template <class T> bool chmin(T& a, T b) {
    if(a > b) { a = b; return true; }
    else return false;
}

constexpr int INF = 1 << 30;

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=ja
int main() {
    int n, m, s;
    cin >> n >> m >> s; // 頂点数、辺の数、始点

    // グラフの読み込み
    using P = pair<int, int>;
    vector<vector<P>> g(n);  // 次の頂点、距離
    while(m--) {
        int a, b, d;
        cin >> a >> b >> d;
        g[a].emplace_back(b, d);    // 0-indexed
    }

    // ダイクストラ法
    // 最短経路を求める。辺は全て非負。計算量はO((E+V)logV)
    vector<int> dist(n, INF);   // 距離
    priority_queue<P, vector<P>, greater<P>> que;    // 距離、頂点
    chmin(dist[s], 0); // 距離の更新はchmin
    que.emplace(0, s);
    while(!que.empty()) {
        int d = que.top().first;
        int v = que.top().second;
        que.pop();
        if(dist[v] < d) continue;   // 古い情報なのでスキップ
        for(auto e : g[v]) {    // 次の頂点、距離
            if(chmin(dist[e.first], d + e.second)) {    // 距離の更新はchmin
                que.emplace(dist[e.first], e.first);
            }
        }
    }

    // 距離の出力
    for(auto i : dist) {
        if(i == INF) cout << "INF" << endl;
        else cout << i << endl;
    }
}