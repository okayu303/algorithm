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

    // 先行順と後行順
    vector<int> pre_order, post_order;
    function<void(int, int)> dfs = [&](int v, int p) {
        pre_order.push_back(v);
        for(int nv : g[v]) {
            if(nv == p) continue;
            dfs(nv, v);
        }
        post_order.push_back(v);
    };

    dfs(0, -1);
    for(int& i : pre_order) cout << i + 1 << ' ';
    cout << endl;
    for(int& i : post_order) cout << i + 1 << ' ';
    cout << endl;
}