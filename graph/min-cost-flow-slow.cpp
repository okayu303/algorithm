#include <bits/stdc++.h>
using namespace std;

using ll = long long;
constexpr ll INFL = 1LL << 60;

struct MinCostFlow {
    struct Edge {
        ll to, cap, cost, rev;
        Edge(ll to, ll cap, ll cost, ll rev) : to(to), cap(cap), cost(cost), rev(rev) {}
    };
    ll V;
    vector<vector<Edge>> g;
    vector<ll> dist, prevv, preve;
    MinCostFlow(ll V) : V(V), g(V), prevv(V), preve(V) {}

    void add_edge(ll from, ll to, ll cap, ll cost) {
        g[from].emplace_back(to, cap, cost, (ll)g[to].size());
        g[to].emplace_back(from, 0, -cost, (ll)g[from].size()-1);
    }

    ll min_cost_flow(ll s, ll t, ll f) {
        ll res = 0;
        while(f > 0) {
            dist.assign(V, INFL);
            dist[s] = 0;
            // ベルマンフォード法で最小コストの残余パスを求める
            bool update = true;
            while(update) {
                update = false;
                for(ll v = 0; v < V; ++v) {
                    if(dist[v] == INFL) continue;
                    for(ll i = 0; i < (ll)g[v].size(); ++i) {
                        Edge& e = g[v][i];
                        if(e.cap > 0 && dist[e.to] > dist[v] + e.cost) {
                            dist[e.to] = dist[v] + e.cost;
                            prevv[e.to] = v;    // 最小コストのパスの前の頂点を記録
                            preve[e.to] = i;    // 前の頂点から出る辺のindexを記録
                            update = true;
                        }
                    }
                }
            }
            if(dist[t] == INFL) return -1;  // 残余パスがない
            // 最小コストのパスの最小容量を求める
            ll d = f;
            for(ll v = t; v != s; v = prevv[v]) {
                d = min(d, g[prevv[v]][preve[v]].cap);
            }
            f -= d;
            res += d * dist[t]; // 流量xコストを足す
            for(ll v = t; v != s; v = prevv[v]) {
                Edge& e = g[prevv[v]][preve[v]];    // eは頂点vに入り込む辺
                e.cap -= d;
                g[v][e.rev].cap += d;
            }
        }
        return res;
    }
};

// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B&lang=jp
int main() {
    ll V, E, F;
    cin >> V >> E >> F;
    MinCostFlow M(V);
    while(E--) {
        ll u, v, c, d;
        cin >> u >> v >> c >> d;
        M.add_edge(u, v, c, d);
    }
    cout << M.min_cost_flow(0, V-1, F) << endl;
}