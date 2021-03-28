#include <bits/stdc++.h>
using namespace std;

using ll = long long;
constexpr ll INFL = 1LL << 60;

struct Dinic {
    struct Edge {
        ll to, cap, rev;
        Edge(ll to, ll cap, ll rev) : to(to), cap(cap), rev(rev) {};
    };
    ll n;
    vector<vector<Edge>> g;
    vector<ll> level;   // 残余パスの視点からの距離
    vector<ll> iter;
    Dinic(ll n) : n(n), g(n), iter(n) {};

    void add_edge(ll from, ll to, ll cap) {
        g[from].emplace_back(to, cap, (ll)g[to].size());
        g[to].emplace_back(from, 0, (ll)g[from].size()-1);  // g[form]は追加後なので1減らす
    }

    // 容量が残っているパスにおける始点からの距離を計算
    void bfs(ll s) {
        level.assign(n, -1);
        queue<ll> que;
        level[s] = 0;
        que.push(s);
        while(!que.empty()) {
            ll v = que.front();
            que.pop();
            for(ll i = 0; i < (ll)g[v].size(); ++i) {
                Edge& e = g[v][i];
                if(e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[v] + 1;
                    que.push(e.to);
                }
            }
        }
    }

    // vから終点tの最短経路の最小flowを計算
    ll dfs(ll v, ll t, ll f) {
        if(v == t) return f;
        // iter[v]を増やすことで各Edgeの探査は1回のみとする
        for(ll& i = iter[v]; i < (ll)g[v].size(); ++i) {
            Edge& e = g[v][i];
            // 容量が残っていて始点sからの距離が増えるなら先に進む
            if(e.cap > 0 && level[v] < level[e.to]) {
                ll d = dfs(e.to, t, min(f, e.cap));
                if(d > 0) {
                    e.cap -= d;
                    g[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    ll max_flow(ll s, ll t) {
        ll flow = 0;
        while(true) {
            bfs(s);
            if(level[t] < 0) return flow;
            iter.assign(n, 0);
            ll f;
            while((f = dfs(s, t, INFL)) > 0) { flow += f; }
        }
    }
};

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A&lang=jp
int main() {
    ll V, E;
    cin >> V >> E;
    Dinic D(V);
    while(E--) {
        ll u, v, c;
        cin >> u >> v >> c;
        D.add_edge(u, v, c);
    }
    cout << D.max_flow(0, V-1) << endl;
}