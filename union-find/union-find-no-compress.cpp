#include <iostream>
#include <vector>
using namespace std;

struct UnionFind {
    vector<int> par;
	vector<int> siz;

    UnionFind(int n) : par(n), siz(n, 1) { for (int i = 0; i < n; ++i) par[i] = i; }

    int root(int x) {
        if (par[x] == x) return x;
        return root(par[x]);
    }

    bool same(int x, int y) { return root(x) == root(y); }
    int size(int x) { return siz[root(x)]; }

    bool merge(int x, int y) {
        x = root(x); y = root(y);
        if (x == y) return false;
        if(size(x) < size(y)) swap(x, y);
        par[y] = x;
		siz[x] += siz[y];
        return true;
    }
};

// https://atcoder.jp/contests/atc001/tasks/unionfind_a
int main() {
    int n, q;
    cin >> n >> q;
    UnionFind uf(n);
    while(q--) {
        int p, a, b;
        cin >> p >> a >> b;
        if(p == 0) uf.merge(a, b);
        else cout << (uf.same(a, b) ? "Yes" : "No") << endl;
    }
}