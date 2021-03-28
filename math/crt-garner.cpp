#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

ll mod(ll a, ll m) { return (a % m + m) % m; }

ll ext_gcd(ll a, ll b, ll& x, ll& y) {
    if(b == 0) { x = 1; y = 0; return a; }
    ll g = ext_gcd(b, a % b, y, x);
    y -= a/b * x;
    return g;
}

ll modinv(ll a, ll m) {
    ll x, y;
    ext_gcd(a, m, x, y);
    return mod(x, m);
}

pair<ll, ll> garner(vector<ll> r, vector<ll> m) {
    int n = r.size();
    vector<ll> mm(n);   // 1, m[0], m[0]m[1]...
    mm[0] = 1;
    for(int i = 1; i < n; ++i) mm[i] = mm[i-1] * m[i-1];
    vector<ll> inv_mm(n);   // mm[0] (mod[0]), mm[1] (mod[1])...
    for(int i = 0; i < n; ++i) inv_mm[i] = modinv(mm[i], m[i]);
    vector<ll> t(n);    // t[0] + t[1]m[0] + ... + t[k]m[0]...m[k-1] = r[k] (mod m[k])
    ll sum_t = 0;   // t[0] + t[1]m[0] + ...
    for(int i = 0; i < n; ++i) {
        t[i] = mod(r[i] - sum_t, m[i]);
        t[i] = mod(t[i] * inv_mm[i], m[i]);
        sum_t += t[i] * mm[i];
    }
    pair<ll, ll> ret;
    ret.first = sum_t;
    ret.second = mm.back() * m.back();
    return ret;
}

int main() {
    ll ans = 10000;
    vector<ll> mod = {5, 7, 11, 13, 17}, rem;
    for(ll i : mod) rem.push_back(ans % i);
    pair<ll, ll> p = garner(rem, mod);
    cout << "rem = " << p.first << " (mod = " << p.second << ")" << endl;
}