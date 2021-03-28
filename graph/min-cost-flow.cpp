#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <class T> bool chmin(T& a, T b) {
    if(a > b) { a = b; return true; }
    else return false;
}

constexpr ll INFL = 1LL << 60;

struct MinCostFlow {
    struct Edge {
        ll to, cap, cost, rev;
        Edge(ll to, ll cap, ll cost, ll rev) : to(to), cap(cap), cost(cost), rev(rev) {}
    };
    using P = pair<ll, ll>;
    ll V;
    vector<vector<Edge>> g;
    vector<ll> h, dist, prevv, preve;
    MinCostFlow(ll V) : V(V), g(V), h(V), prevv(V), preve(V) {}

    void add_edge(ll from, ll to, ll cap, ll cost) {
        g[from].emplace_back(to, cap, cost, (ll)g[to].size());
        g[to].emplace_back(from, 0, -cost, (ll)g[from].size()-1);
    }

    // 戻り値は(最大流量, コスト)のペア
    pair<ll, ll> min_cost_flow(ll s, ll t, ll f) {
        ll f_orig = f;
        ll res = 0;
        h.assign(V, 0);
        // ダイクストラ法で最小コストの残余パスを求める
        while(f > 0) {
            priority_queue<P, vector<P>, greater<P>> que;
            dist.assign(V, INFL);
            dist[s] = 0;
            que.emplace(0, s);
            while(!que.empty()) {
                P p = que.top();
                que.pop();
                ll v = p.second;
                if(dist[v] < p.first) continue;
                for(ll i = 0; i < (ll)g[v].size(); ++i) {
                    Edge& e = g[v][i];
                    if(e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
                        dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
                        prevv[e.to] = v;    // コストが最短となるパスの前の頂点を記録
                        preve[e.to] = i;
                        que.emplace(dist[e.to], e.to);
                    }
                }
            }
            if(dist[t] == INFL) return {f_orig-f, res};  // 残余パスがない
            for(ll v = 0; v < V; ++v) h[v] += dist[v];
            // 始点から終点に可能な限り流す
            ll d = f;
            for(ll v = t; v != s; v = prevv[v]) {
                d = min(d, g[prevv[v]][preve[v]].cap);
            }
            f -= d;
            res += d * h[t];
            for(ll v = t; v != s; v = prevv[v]) {
                Edge& e = g[prevv[v]][preve[v]];
                e.cap -= d;
                g[v][e.rev].cap += d;
            }
        }
        return {f_orig-f, res};
    }
};

// https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/6/GRL_6_B
int main() {
    ll V, E, F;
    cin >> V >> E >> F;
    MinCostFlow M(V);
    while(E--) {
        ll u, v, c, d;
        cin >> u >> v >> c >> d;
        M.add_edge(u, v, c, d);
    }
    pair<ll, ll> ans = M.min_cost_flow(0, V-1, F);
    if(ans.first == F) cout << ans.second << endl;
    else cout << -1 << endl;
}