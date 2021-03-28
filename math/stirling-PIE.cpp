#include <bits/stdc++.h>
using namespace std;

struct mint {
    static const long long mod = 1000000007;
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

struct combi {
    const static long long mod = mint::mod;
    int n;
    vector<mint> fac, finv, inv;
    
    combi(int _n) : n(_n + 1), fac(n, 1), finv(n, 1), inv(n, 1) {
        for (int i = 2; i < n; ++i) {
            fac[i] = fac[i - 1] * i;
            inv[i] =- inv[mod % i] * (mod / i);
            finv[i] = finv[i - 1] * inv[i];
        }
    };

    mint get(int n, int k) {
        if(n < k) return 0;
        if(n < 0 || k < 0) return 0;
        mint ret = fac[n] * finv[k] * finv[n - k];
        return ret;
    }
};

// スターリング数を包除原理を使って求める
// n個のボールをk個の区別しない箱に1つ以上入れる場合の数（n個のボールをkのグループに分ける）
mint stirling(int n, int k) {
    combi C(k);
    mint ans = 0;

    // 区別「する」k個の箱に入れる場合の数
    // 「1の箱が空 or 2の箱が空 or ..」の集合の余事象を考える
    for(int i = 0; i < k; ++i) {
        mint ans2 = C.get(k, i);    // i個の空箱の選び方
        ans2 *= mint(k-i).pow(n);    // 残り(k-i)個にn個のボールを入れる。入れるボールの数は問わない
        if(i%2 == 0) ans += ans2;   // 空箱の数が0, 2, ..だと足す
        else ans -= ans2;           // 空箱の数が1, 3, ..だと引く
    }

    // 区別「しない」k個の箱に入れる場合の数
    ans *= C.finv[k];
    return ans;
}

// https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/5/DPL_5_I
int main() {
    int n, k;
    cin >> n >> k;
    cout << stirling(n, k) << endl;
    return;
}