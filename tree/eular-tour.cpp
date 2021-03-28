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

    // オイラーツアー
    vector<int> eular_tour;
    function<void(int, int)> dfs = [&](int v, int p) {
        eular_tour.push_back(v);
        for(int nv : g[v]) {
            if(nv == p) continue;
            dfs(nv, v);
            eular_tour.push_back(v);
        }
    };
    
    dfs(0, -1);
    for(int& i : eular_tour) cout << i + 1 << ' ';
    cout << endl;
}