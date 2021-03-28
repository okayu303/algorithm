#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// x^eをmで割った余り
ll mod_pow(ll x, ll e, ll m) {
    if(e == 0) return 1;
    ll res = mod_pow(x, e >> 1, m);
    res = res * res;
    if(e & 1) res *= x;
    res %= m;
    return res;
}

int main() {
    ll x, e, m;
    cin >> x >> e >> m;
    cout << mod_pow(x, e, m) << endl;
}