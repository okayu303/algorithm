#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 1 << 30;
struct UnionFind {
    int now;
    vector<int> par, rank, time;
    vector<vector<pair<int, int>>> siz;

    UnionFind(int n) : now(0), par(n), siz(n, vector<pair<int, int>>(1, make_pair(0, 1))), rank(n, 0), time(n, INF) {
        for (int i = 0; i < n; ++i) par[i] = i;
    }

    int find(int x, int t) {
        if(t < time[x]) return x;
        else return find(par[x], t);
    }

    bool same(int x, int y, int t) { return find(x, t) == find(y, t); }

    bool merge(int x, int y) {
        ++now;
        x = find(x, now); y = find(y, now);
        if (x == y) return false;
        if(rank[x] < rank[y]) swap(x, y);
        siz[x].push_back(make_pair(now, size(x, now) + size(y, now)));
        par[y] = x;
        time[y] = now;
        if(rank[x] == rank[y]) ++rank[x];
        return true;
    }

    int size(int x, int t) {
        x = find(x, t);
        auto itr = upper_bound(siz[x].begin(), siz[x].end(), make_pair(t, INF));
        --itr;
        return itr->second;
    }
};

// https://atcoder.jp/contests/code-thanks-festival-2017-open/tasks/code_thanks_festival_2017_h
int main() {
    int n, m;
    cin >> n >> m;
    UnionFind uf(n);
    int m2 = m;
    while(m2--) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        uf.merge(a, b);
    }
    int q;
    cin >> q;
    while(q--) {
        int x, y;
        cin >> x >> y;
        --x, --y;
        int ok = m+1, ng = 0;
        while(ok - ng > 1) {
            int mid = (ok + ng) / 2;
            if(uf.same(x, y, mid)) ok = mid;
            else ng = mid;
        }
        if(ok == m+1) cout << -1 << endl;
        else cout << ok << endl;
    }
}