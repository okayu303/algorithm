#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// オイラーのPhi関数のテーブルを作る。計算量はO(n)
// Phi関数は1,2,..,nでnと互いに素の数の個数
vector<ll> euler_phi(ll n) {
    vector<ll> res(n+1);
    for(int i = 0; i <= n; ++i) res[i] = i;
    for(int i = 2; i <= n; ++i) {
        if(res[i] != i) continue;   // 素数でない場合はスキップ
        // 素数iで割り切れるjに対して、割り切れる自然数の数を引いていく
        for(int j = i; j <= n; j += i) res[j] = res[j] / i * (i-1);
    }
    return res;
}

int main() {
    ll n;
    cin >> n;
    vector<ll> euler = euler_phi(n);
    for(auto i : euler) cout << i << ' ';
    cout << endl;
}