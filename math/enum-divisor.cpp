#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// 約数の列挙
// nの全ての約数を返す。計算量はO(√n)
vector<ll> divisor(ll n) {
    vector<ll> ret, ret2;
    for(ll i = 1; i*i <= n; ++i) {
        if(n % i == 0) {
            ret.push_back(i);
            if(i < n/i) ret2.push_back(n/i);
        }
    }
    reverse(ret2.begin(), ret2.end());
    ret.insert(ret.end(), ret2.begin(), ret2.end());
    return ret;
}

// https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/3/ITP1_3_D
int main() {
    ll a, b, c;
    cin >> a >> b >> c;
    vector<ll> div = divisor(c);
    ll ans = upper_bound(div.begin(), div.end(), b) - lower_bound(div.begin(), div.end(), a);
    cout << ans << endl;
}