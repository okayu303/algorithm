#include <iostream>
#include <vector>
using namespace std;

template<class Abel> struct UnionFind {
    vector<int> par;
	vector<int> siz;
    vector<Abel> diff_weight;

    UnionFind(int n = 1, Abel UNITY = 0) : par(n), siz(n, 1), diff_weight(n, UNITY) {
        for (int i = 0; i < n; ++i) par[i] = i;
    }

    int root(int x) {
        if (par[x] == x) return x;
        else {
            int r = root(par[x]);
            diff_weight[x] += diff_weight[par[x]];
            return par[x] = r;
        }
    }

    Abel weight(int x) {
        root(x);
        return diff_weight[x];
    }

    bool same(int x, int y) { return root(x) == root(y); }
    int size(int x) { return siz[root(x)]; }

    bool merge(int x, int y, Abel w) {
        w += weight(x); w -= weight(y);
        x = root(x); y = root(y);
        if (x == y) return false;
        if(size(x) < size(y)) swap(x, y), w = -w;
        par[y] = x;
		siz[x] += siz[y];
        diff_weight[y] = w;
        return true;
    }

    Abel diff(int x, int y) { return weight(y) - weight(x); }
};

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B&lang=jp
int main() {
    int n, q;
    cin >> n >> q;
    UnionFind<int> uf(n, 0);
    while(q--) {
        int t, x, y;
        cin >> t >> x >> y;
        if(t == 0) {
            int z;
            cin >> z;
            uf.merge(x, y, z);
        }
        else if(uf.same(x, y)) {
            cout << uf.diff(x, y) << endl;
        }
        else cout << '?' << endl;
    }
}