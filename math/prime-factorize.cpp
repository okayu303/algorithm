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

// https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/1/NTL_1_A
int main() {
    ll n;
    cin >> n;
    vector<pair<ll, ll>> f = prime_factorize(n);
    cout << n << ':';
    for(auto i : f) {
        for(int j = 0; j < i.second; ++j) cout << ' ' << i.first;
    }
    cout << endl;
}