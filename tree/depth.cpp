#include <bits/stdc++.h>
using namespace std;

int main() {
    // グラフの入力
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    for(int i = 0; i < n-1; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    // 深さ
    vector<int> depth(n);
    function<void(int, int)> dfs = [&](int v, int p) {
        for(int nv : g[v]) {
            if(nv == p) continue;
            depth[nv] = depth[v] + 1;
            dfs(nv, v);
        }
    };

    dfs(0, -1);
    for(int& i : depth) cout << i << ' ';
    cout << endl;
}