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

    // 部分木のサイズ
    vector<int> subtree_size(n);
    function<int(int, int)> dfs = [&](int v, int p) {
        int size = 1;
        for(int nv : g[v]) {
            if(nv == p) continue;
            size += dfs(nv, v);
        }
        return subtree_size[v] = size;
    };
    
    dfs(0, -1);
    for(int& i : subtree_size) cout << i << ' ';
    cout << endl;
}