#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// 負の数にも対応したmod
inline ll mod(ll a, ll m) {
    return (a % m + m) % m;
}

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

// ax=1(mod m)となるxを返す。解なしだと-1を返す
ll mod_inv(ll a, ll m) {
    ll x, y, d;
    // ax+my=1を満たす(x,y)を計算。gcd(a,m)が1以外だと解なし
    d = ext_gcd(a, m, x, y);
    if(d == 1) return mod(x, m);
    else return -1;
}

int main() {
    ll a, m;
    cin >> a >> m;
    ll minv = mod_inv(a, m);
    cout << minv << endl;
}