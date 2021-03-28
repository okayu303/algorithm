#include <bits/stdc++.h>
using namespace std;

template <class T> bool chmax(T& a, T b) {
    if(a < b) { a = b; return true; }
    else return false;
}

struct Graph {
    int n;
    vector<vector<int>> graph;
    vector<int> depth, par;

    Graph(int n) : n(n), graph(n), depth(n), par(n) {}

    void add_edge(int u, int v) {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    void dfs(int v, int p = -1) {
        par[v] = p;
        for(auto nv : graph[v]) {
            if(nv == p) continue;
            depth[nv] = depth[v] + 1;
            dfs(nv, v);
        }
    }
};

struct LCA {
    Graph& g;
    vector<vector<int>> par;

    LCA(Graph& g) : g(g) {
        g.dfs(0);
        init();
    };

    void init() {
        int max_d = 0;
        int n = g.n;
        for(int i = 0; i < n; ++i) chmax(max_d, g.depth[i]);
        int log_d = 0;
        while((1 << log_d) < max_d) ++log_d;    // 2^log_d >= max_dとする
        par = vector<vector<int>>(log_d + 1, vector<int>(n, -1));
        par[0] = g.par;
        for(int i = 1; i <= log_d; ++i) {
            for(int j = 0; j < n; ++j) {
                if(par[i-1][j] == -1) continue;
                par[i][j] = par[i-1][par[i-1][j]];
            }
        }
    }

    int lca(int u, int v) {
        if(g.depth[u] < g.depth[v]) swap(u, v); // uの方を深くする
        int log_d = par.size();
        // uとvの深さを合わせる
        for(int i = 0; i < log_d; ++i) {
            if((g.depth[u] - g.depth[v]) & (1 << i)) u = par[i][u]; // uの深さを2^iだけ少なくする
        }
        if(u == v) return u;
        for(int i = log_d - 1; i >= 0; --i) {
            if(par[i][u] == par[i][v]) continue;
            u = par[i][u], v = par[i][v];   // 親が異なる場合は根に向かって移動
        }
        return par[0][u];
    }
};

// https://atcoder.jp/contests/abc014/tasks/abc014_4
int main() {
    int n;
    cin >> n;
    Graph G(n);
    for(int i = 0; i < n-1; ++i) {
        int x, y;
        cin >> x >> y;
        --x, --y;
        G.add_edge(x, y);
    }

    LCA L(G);
    int q;
    cin >> q;
    while(q--) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        int c = L.lca(a, b);
        cout << G.depth[a] + G.depth[b] - 2*G.depth[c] + 1 << endl;
    }
}