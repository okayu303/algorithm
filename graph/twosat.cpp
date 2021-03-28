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

struct TwoSat {
    int n;
    SCC s;  // 0~n-1はtrue, n~2n-1はfalse
    vector<int> cmp;
    TwoSat(int n) : n(n), s(2*n), cmp(2*n) {};

    // (Xi=f or Xj=g)のクロージャを追加
    void add_clause(int i, bool f, int j, bool g) {
        int ni = i, nj = j; // (i,f),(j,g)の否定
        if(!f) i += n;
        if(!g) j += n;
        if(f) ni += n;
        if(g) nj += n;
        s.add_edge(ni, j);
        s.add_edge(nj, i);
    }

    // 条件を満たす割当が存在するか判定
    bool satisfable() {
        auto scc = s.scc();
        int sz = scc.size();
        for(int i = 0; i < sz; ++i) {
            for(auto j : scc[i]) cmp[j] = i;
        }
        for(int i = 0; i < n; ++i) {
            // 同じ連結成分にいるため割当は存在しない
            if(cmp[i] == cmp[i+n]) return false;
        }
        return true;
    }

    // クローズを満たす割当を返す
    vector<bool> answer() {
        vector<bool> res(n);
        for(int i = 0; i < n; ++i) {
            // ^X=>Xを満たすためにはX=true
            if(cmp[i] > cmp[i+n]) res[i] = true;
        }
        return res;
    }
};

// https://atcoder.jp/contests/practice2/tasks/practice2_h
int main() {
    int n, d;
    cin >> n >> d;
    vector<int> x(n), y(n);
    for(int i = 0; i < n; ++i) cin >> x[i] >> y[i];

    TwoSat ts(n);   // xに置く場合をtrue, yに置く場合をfalseとする
    for(int i = 0; i < n; ++i) {
        for(int j = i+1; j < n; ++j) {
            if(abs(x[i] - x[j]) < d) ts.add_clause(i, false, j, false); // iとjのいずれかはyに置く
            if(abs(x[i] - y[j]) < d) ts.add_clause(i, false, j, true);
            if(abs(y[i] - x[j]) < d) ts.add_clause(i, true, j, false);
            if(abs(y[i] - y[j]) < d) ts.add_clause(i, true, j, true);
        }
    }
    bool ans = ts.satisfable();
    cout << (ans ? "Yes" : "No") << endl;
    if(ans) {
        vector<bool> ans2 = ts.answer();
        for(int i = 0; i < n; ++i) {
            if(ans2[i]) cout << x[i] << endl;
            else cout << y[i] << endl;
        }
    }
}