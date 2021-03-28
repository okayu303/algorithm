#include <bits/stdc++.h>
using namespace std;

struct SCC {
    using Graph = vector<vector<int>>;
    int V;
    Graph g, rg;    // rgは逆向きのグラフ
    vector<int> post_order, tmp;
    vector<bool> seen;
    SCC(int V) : V(V), g(V), rg(V) {};

    void add_edge(int u, int v) {
        g[u].push_back(v);
        rg[v].push_back(u);
    }

    // 後行順に探索した結果を求める
    void dfs_post(int v) {
        seen[v] = true;
        for(int nv : g[v]) {
            if(seen[nv]) continue;
            dfs_post(nv);
        }
        post_order.push_back(v);
    }

    // 各連結成分を求める
    void dfs_scc(int v) {
        seen[v] = true;
        tmp.push_back(v);
        for(int nv : rg[v]) {
            if(seen[nv]) continue;
            dfs_scc(nv);
        }
    }

    // res[i]は同じ連結成分の頂点の集合
    vector<vector<int>> scc() {
        // 後行順を逆に並べる。DFSで探索できる先の頂点ほど前に来る
        seen.assign(V, false);
        for(int i = 0; i < V; ++i) {
            if(seen[i]) continue;
            dfs_post(i);
        }
        reverse(post_order.begin(), post_order.end());

        // 移動先の頂点から逆向きグラフで移動できる頂点は強連結となる
        vector<vector<int>> res;
        seen.assign(V, false);
        for(int i = 0; i < V; ++i) {
            int v = post_order[i];
            if(seen[v]) continue;
            tmp.clear();
            dfs_scc(v);
            res.push_back(tmp);
        }
        return res;
    }
};

// https://atcoder.jp/contests/practice2/tasks/practice2_g
int main() {
    int n, m;
    cin >> n >> m;
    SCC S(n);
    while(m--) {
        int a, b;
        cin >> a >> b;
        S.add_edge(a, b);
    }

    auto scc = S.scc();
    cout << (int)scc.size() << endl;
    for(auto i : scc) {
        cout << (int)i.size();;
        for(auto j : i) cout << ' ' << j;
        cout << endl;
    }
}