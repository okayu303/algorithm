#include <iostream>
#include <vector>
#include <functional>

using namespace std;
using ll = long long;
constexpr ll INFL = 1LL << 60;

template <typename X, typename M>
struct SegTreeLazy {
    using FXX = function<X(X, X)>;
    using FMX = function<X(M, X)>;
    using FMM = function<M(M, M)>;  // 右から作用する
    int n;
    FXX xx;
    FMX mx;
    FMM mm;
    const X ex;
    const M em;
    vector<X> dat;
    vector<M> lazy;

    SegTreeLazy(int _n, FXX xx, FMX mx, FMM mm, X ex, M em)
        : xx(xx), mx(mx), mm(mm), ex(ex), em(em) {
        n = 1;
        while(n < _n) n *= 2;
        dat.assign(2 * n - 1, ex);
        lazy.assign(2 * n - 1, em);
    }

    void update_fast(int i, X x) { dat[i + n - 1] = x; }
    void build() {
        for(int i = n - 2; i >= 0; --i) {
            dat[i] = xx(dat[2 * i + 1], dat[2 * i + 2]);
        }
    }
    void update(vector<X> v) {
        for(int i = 0; i < v.size(); ++i) update_fast(i, v[i]);
        build();
    }

    void eval(int k) {
        if(k < n - 1) {
            lazy[2 * k + 1] = mm(lazy[k], lazy[2 * k + 1]);
            lazy[2 * k + 2] = mm(lazy[k], lazy[2 * k + 2]);
        }
        dat[k] = mx(lazy[k], dat[k]);
        lazy[k] = em;
    }

    void update(int a, int b, M x, int k, int l, int r) {
        eval(k);
        if(a <= l && r <= b) {
            lazy[k] = mm(x, lazy[k]);
            eval(k);
        }
        else if(a < r && l < b) {
            update(a, b, x, k * 2 + 1, l, (l + r) / 2);
            update(a, b, x, k * 2 + 2, (l + r) / 2, r);
            dat[k] = xx(dat[k * 2 + 1], dat[k * 2 + 2]);
        }
    }
    void update(int a, int b, M x) { update(a, b, x, 0, 0, n); }

    X query(int a, int b, int k, int l, int r) {
        eval(k);
        if(r <= a || b <= l) return ex;
        if(a <= l && r <= b) return dat[k];
        else {
            X lx = query(a, b, k * 2 + 1, l, (l + r) / 2);
            X rx = query(a, b, k * 2 + 2, (l + r) / 2, r);
            return xx(lx, rx);
        }
    }
    X query(int a, int b) { return query(a, b, 0, 0, n); }
};

void show(SegTreeLazy<ll, ll>& st) {
    for(int i = 0; i < 10; ++i) cout << st.query(i, i + 1) << ' ';
    cout << endl;
}

struct mint {
    static const long long mod = 998244353;
    long long x;
    mint(long long x = 0) : x((x % mod + mod) % mod) {}
    mint operator-() const { return mint(-x);}
    mint& operator+=(const mint& a) {if ((x += a.x) >= mod) x -= mod; return *this;}
    mint& operator-=(const mint& a) {if ((x += mod - a.x) >= mod) x -= mod; return *this;}
    mint& operator*=(const mint& a) {(x *= a.x) %= mod; return *this;}

    friend const mint operator+(const mint& a, const mint& b) { mint ret = a; return ret += b; }
    friend const mint operator-(const mint& a, const mint& b) { mint ret = a; return ret -= b; }
    friend const mint operator*(const mint& a, const mint& b) { mint ret = a; return ret *= b; }
    friend ostream& operator<<(ostream& s, const mint& a) { return s << a.x; }

    mint pow(long long t) const {
        if (!t) return 1;
        mint a = pow(t >> 1);
        a *= a;
        if (t & 1) a *= *this;
        return a;
    }

    // for prime mod
    mint inv() const { return pow(mod - 2);}
    mint& operator/=(const mint a) { return (*this) *= a.inv();}
    friend const mint operator/(const mint& a, const mint& b) { mint ret = a; return ret /= b; }
};

template <class T> ostream& operator<<(ostream& s, const vector<T>& a) {
    for(auto i : a) s << i << ' ';
    return s;
}

int main() {
    struct X { mint x; ll size; };
    struct M { mint b, c; };
    auto xx = [](X a, X b) -> X { return X{a.x + b.x, a.size + b.size}; };
    auto mx = [](M f, X a) -> X { return X{f.b * a.x + f.c * a.size, a.size}; };
    auto mm = [](M f, M g) -> M { return M{f.b * g.b, f.b * g.c + f.c}; };
    X ex = {0, 0};
    M em = {1, 0};

    ll n, q;
    cin >> n >> q;
    vector<X> a(n, {0, 1});
    for(int i = 0; i < n; ++i) cin >> a[i].x.x;

    SegTreeLazy<X, M> st(n, xx, mx, mm, ex, em);
    st.update(a);
    while(q--) {
        ll t;
        cin >> t;
        if(t == 0) {
            ll l, r, b, c;
            cin >> l >> r >> b >> c;
            st.update(l, r, {b, c});
        }
        else {
            ll l, r;
            cin >> l >> r;
            cout << st.query(l, r).x << endl;
        }
    }
}