#include <iostream>
#include <vector>
#include <functional>
using namespace std;

using ll = long long;
constexpr ll INFL = 1LL << 60;

template <class X>
struct SegTree {
    using OP = function<X(X, X)>;
    int n;
    OP op;
    const X e;
    vector<X> dat;

    SegTree(int n_, OP op, X e) : op(op), e(e) {
        int m = 1;
        while(m < n_) m *= 2;
        n = m;
        dat.assign(2*n-1, e);
    }

    void update_fast(int i, X x) { dat[i+n-1] = x; }
    void build() {
        for(int i = n-2; i >= 0; --i) {
            dat[i] = op(dat[2*i+1], dat[2*i+2]);
        }
    }
    void update(vector<X> v) {
        for(int i = 0; i < v.size(); ++i) update_fast(i, v[i]);
        build();
    }

    void update(int i, X x) {
        i += n - 1;
        dat[i] = x;
        while(i > 0) {
            i = (i - 1) / 2;
            dat[i] = op(dat[i * 2 + 1], dat[i * 2 + 2]);
        }
    }

    X query_sub(int a, int b, int k, int l, int r) {
        if(r <= a || b <= l) return e;
        if(a <= l && r <= b) return dat[k];
        else {
            X vl = query_sub(a, b, k * 2 + 1, l, (l + r) / 2);
            X vr = query_sub(a, b, k * 2 + 2, (l + r) / 2, r);
            return op(vl, vr);
        }
    }

    X query(int a, int b) { // query for [a, b)
        return query_sub(a, b, 0, 0, n);
    }
};

int main() {
    //              0  1  2  3  4  5  6  7  8  9
    vector<ll> a = {2, 3, 1, 9, 3, 4, 2, 7, 3, 1};

    using Func = function<ll(ll, ll)>;
    Func Fx = [](ll a, ll b) -> ll { return min(a, b); };
    SegTree<ll> st_min(a.size(), Fx, INFL);
    st_min.update(a);
    cout << "Range Min Query" << endl;

    Fx = [](ll a, ll b) -> ll { return max(a, b); };
    SegTree<ll> st_max(a.size(), Fx, -INFL);
    st_max.update(a);
    cout << "Range Max Query" << endl;
    cout << st_max.query(0, 10) << endl;
    cout << st_max.query(3, 6) << endl;

    Fx = [](ll a, ll b) -> ll { return a + b; };
    SegTree<ll> st_add(a.size(), Fx, 0);
    st_add.update(a);
    cout << "Range Add Query" << endl;
    cout << st_add.query(0, 10) << endl;
    cout << st_add.query(3, 6) << endl;
}