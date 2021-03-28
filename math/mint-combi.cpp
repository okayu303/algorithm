#include <iostream>
#include <vector>
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

int main() {
    long long x = 1000000;
    mint m = x;
    cout << m << endl;
    cout << "add" << endl;
    cout << 5 + m << endl;
    cout << m + 5 << endl;
    cout << m + m << endl;

    cout << "sub" << endl;
    cout << 5 - m << endl;
    cout << m - 5 << endl;
    cout << m - m << endl;

    cout << "multi" << endl;
    cout << m * m << endl;
    cout << 5 * m << endl;
    cout << m * 5 << endl;

    cout << "div" << endl;
    cout << m / 5 << endl;
    cout << 5 / m << endl;
    cout << m / m << endl;

    cout << "com" << endl;
    combi com(10000);
    cout << com.get(10, 5) << endl;
    cout << com.get(10000, 1000) << endl;
}