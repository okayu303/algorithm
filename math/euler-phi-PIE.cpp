#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// 素因数分解
// nの(素因数、指数)のペアを返す。計算量はO(√nlogn)
vector<pair<ll, ll>> prime_factorize(ll n) {
    vector<pair<ll, ll>> ret;
    for(ll i = 2; i*i <= n; ++i) {
        if(n % i != 0) continue;
        ll ex = 0;
        while(n % i == 0) {
            ++ex;
            n /= i;
        }
        ret.push_back({i, ex});
    }
    if(n > 1) ret.push_back({n, 1});
    return ret;
}

// オイラーのPhi関数を包除原理で求める。計算量はO(√nlogn)
// 1,2,..,nでnと互いに素の数の個数を返す
ll euler_phi(ll n) {
    vector<pair<ll, ll>> f = prime_factorize(n);
    int sz = f.size();
    ll ret = 0;
    // iの各bitで素因数で割り切れるかを表す
    for(int i = 0; i < (1 << sz); ++i) {
        ll mul = 1;
        for(int j = 0; j < sz; ++j) {
            if(i >> j & 1) mul *= f[j].first;   // 各素因数を掛ける
        }
        // n/mulは集合iの全ての素因数で割り切れる数
        if(__builtin_popcount(i) % 2) ret -= n / mul;
        else ret += n / mul;
    }
    return ret;
}

// https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/1/NTL_1_D
int main() {
    ll n;
    cin >> n;
    cout << euler_phi(n) << endl;
}