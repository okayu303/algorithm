#include <bits/stdc++.h>
using namespace std;

using ll = long long;
constexpr ll INFL = 1LL << 60;

struct FordFulkerson {
    struct Edge {
        ll to, cap, rev;
        Edge(ll to, ll cap, ll rev) : to(to), cap(cap), rev(rev) {};
    };
    ll n;
    vector<vector<Edge>> g;
    vector<bool> used;
    FordFulkerson(ll n) : n(n), g(n) {};

    void add_edge(ll from, ll to, ll cap) {
        g[from].emplace_back(to, cap, (ll)g[to].size());
        g[to].emplace_back(from, 0, (ll)g[from].size()-1);
    }

    ll dfs(ll v, ll t, ll f) {
        if(v == t) return f;    // 終点に到達した時のminのflow
        used[v] = true;
        for(ll i = 0; i < (ll)g[v].size(); ++i) {
            Edge& e = g[v][i];
            if(!used[e.to] && e.cap > 0) {
                ll d = dfs(e.to, t, min(f, e.cap)); // 先に進むごとにe.capとのminに減らす
                if(d > 0) {
                    e.cap -= d;
                    g[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;   // 終点に到達しなければflowの増量は0
    }

    ll max_flow(ll s, ll t) {
        ll flow = 0;
        while(true) {
            used.assign(n, false);
            ll f = dfs(s, t, INFL); // 終点に到達した時のminのflow
            if(f == 0) return flow;
            flow += f;
        }
    }
};

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A&lang=jp
int main() {
    ll V, E;
    cin >> V >> E;
    FordFulkerson F(V);
    while(E--) {
        ll u, v, c;
        cin >> u >> v >> c;
        F.add_edge(u, v, c);
    }
    cout << F.max_flow(0, V-1) << endl;
}