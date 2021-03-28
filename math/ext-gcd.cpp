#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// 拡張ユークリッドの互除法
// ax + by = gcd(a, b)を満たす(x, y)を計算。gcd(a, b)を返す
ll ext_gcd(ll a, ll b, ll& x, ll& y) {
    if(b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll d = ext_gcd(b, a%b, y, x);
    y -= a/b * x;
    return d;
}

// https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/1/NTL_1_E
int main() {
    ll a, b;
    cin >> a >> b;
    ll x, y;
    ext_gcd(a, b, x, y);
    cout << x << ' ' << y << endl;
}