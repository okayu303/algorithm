#include <bits/stdc++.h>
using namespace std;

struct Graph {
    int n;
    vector<vector<int>> g;
    vector<int> depth, eular;

    Graph(int n) : n(n), g(n), depth(n) {};

    void add_edge(int u, int v) {
        g[v].push_back(u);
        g[u].push_back(v);
    }

    void dfs(int v, int p = -1) {
        eular.push_back(v);
        for(int nv : g[v]) {
            if(nv == p) continue;
            depth[nv] = depth[v] + 1;
            dfs(nv, v);
            eular.push_back(v);
        }
    }
};

template <class X>
struct SegTree {
    using OP = function<X(X, X)>;
    int n;
    OP op;
    const X e;
    vector<X> dat;

    SegTree(int n_, OP op, X e) : op(op), e(e) {
        int m = 1;
        while(m < n_) m *= 2;
        n = m;
        dat.assign(2*n-1, e);
    }

    void update_fast(int i, X x) { dat[i+n-1] = x; }
    void build() {
        for(int i = n-2; i >= 0; --i) {
            dat[i] = op(dat[2*i+1], dat[2*i+2]);
        }
    }
    void update(vector<X> v) {
        for(int i = 0; i < v.size(); ++i) update_fast(i, v[i]);
        build();
    }

    void update(int i, X x) {
        i += n - 1;
        dat[i] = x;
        while(i > 0) {
            i = (i - 1) / 2;
            dat[i] = op(dat[i * 2 + 1], dat[i * 2 + 2]);
        }
    }

    X query_sub(int a, int b, int k, int l, int r) {
        if(r <= a || b <= l) return e;
        if(a <= l && r <= b) return dat[k];
        else {
            X vl = query_sub(a, b, k * 2 + 1, l, (l + r) / 2);
            X vr = query_sub(a, b, k * 2 + 2, (l + r) / 2, r);
            return op(vl, vr);
        }
    }

    X query(int a, int b) { // query for [a, b)
        return query_sub(a, b, 0, 0, n);
    }
};

struct LCA {
    using P = pair<int, int>;
    function<P(P, P)> op = [](P a, P b) -> P { return min(a, b); };
    P e = make_pair(1 << 30, 1 << 30);
    SegTree<P> st;  // オイラーツアーにおける(depth, 頂点)のペア
    Graph& g;
    vector<int> fst;    // オイラーツアーで最初に到達するindex

    LCA(Graph& g) : g(g), fst(g.n, -1), st((int)g.eular.size(), op, e) {
        assert((int)g.eular.size() > 0);
        vector<P> p;
        for(int i = 0; i < (int)g.eular.size(); ++i) {
            int v = g.eular[i];
            if(fst[v] == -1) fst[v] = i;
            p.emplace_back(g.depth[v], v);
        }
        st.update(p);
    }

    // オイラーツアー内でuとvの最初に訪れるindex間でdepthが最小となる頂点を求める
    int lca(int u, int v) {
        int fu = fst[u], fv = fst[v];
        if(fu > fv) swap(fu, fv);
        pair<int, int> p = st.query(fu, fv + 1);
        return p.second;
    }
};

// https://atcoder.jp/contests/abc014/tasks/abc014_4
int main() {
    int n;
    cin >> n;
    Graph G(n);
    for(int i = 0; i < n-1; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        G.add_edge(a, b);
    }
    G.dfs(0);   // LCA内のSegTreeのサイズ確定のため事前にdfs

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