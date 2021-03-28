#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

ll mod(ll a, ll m) { return (a%m + m) % m; }

ll ext_gcd(ll a, ll b, ll& x, ll& y) {
    if(b == 0) { x = 1; y = 0; return a; }
    ll g = ext_gcd(b, a % b, y, x);
    y -= a/b * x;
    return g;
}

pair<ll, ll> crt_extgcd(const vector<ll>& r, const vector<ll>& m) {
    pair<ll, ll> ret;
    ll& rem = ret.first;
    ll& mod = ret.second;
    rem = 0, mod = 1;
    for(int i = 0; i < (int)r.size(); ++i) {
        ll inv_mod, _;
        ll div = ext_gcd(mod, m[i], inv_mod, _);    // mod*inv_mod = 1 (mod m[i]/div)
        if((r[i] - rem) % div != 0) return make_pair(0, -1);
        ll tmp = (r[i] - rem) / div * inv_mod % (m[i] / div);
        rem += mod * tmp;
        mod *= m[i] / div;    // lcm(m, m[i])
    }
    rem = (rem % mod + mod) % mod;
    return ret;
}

int main() {
    vector<ll> mod = {3, 5};
    vector<ll> rem = {2, 3};
    pair<ll, ll> p = crt_extgcd(rem, mod);
    cout << "rem = " << p.first << " (mod = " << p.second << ")" << endl;
}