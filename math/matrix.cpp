#include <bits/stdc++.h>
using namespace std;

struct mint {
    static const long long mod = 1000000007;
    static const bool print_minus = false;
    long long x;
    mint(long long x = 0) : x((x % mod + mod) % mod) {}
    mint operator-() const { return mint(-x);}
    mint& operator+=(const mint& a) {if ((x += a.x) >= mod) x -= mod; return *this;}
    mint& operator-=(const mint& a) {if ((x += mod - a.x) >= mod) x -= mod; return *this;}
    mint& operator*=(const mint& a) {(x *= a.x) %= mod; return *this;}

    friend const mint operator+(const mint& a, const mint& b) { mint ret = a; return ret += b; }
    friend const mint operator-(const mint& a, const mint& b) { mint ret = a; return ret -= b; }
    friend const mint operator*(const mint& a, const mint& b) { mint ret = a; return ret *= b; }
    friend ostream& operator<<(ostream& s, const mint& a) {
        if(print_minus) {
            const long long th = 10000;
            if(a.x > th) return s << a.x - mod;
        }
        return s << a.x;
    }

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

template <class T>
struct Matrix {
    int n, m;
    vector<vector<T>> dat;

    Matrix(int n, int m) : n(n), m(m), dat(n, vector<T>(m)) {}
    Matrix(const vector<vector<T>>& a) : n((int)a.size()), m((int)a[0].size()), dat(a) {}

    Matrix operator-() const {
        Matrix res(n, m);
        for(int i = 0; i < n; ++i) for(int j = 0; j < n; ++j) res[i][j] = -dat[i][j];
        return res;
    }

    Matrix& operator*=(const Matrix& a) {
        assert(m == a.n);
        Matrix res(n, a.m);
        for(int i = 0; i < n; ++i) for(int j = 0; j < a.m; ++j) for(int k = 0; k < m; ++k) {
            res[i][j] += dat[i][k] * a[k][j];
        }
        return *this = res;
    }

    Matrix& operator+=(const Matrix& a) {
        assert(n == a.n && m == a.m);
        for(int i = 0; i < n; ++i) for(int j = 0; j < m; ++j) dat[i][j] += a[i][j];
        return *this;
    }

    Matrix& operator*=(T a) {
        for(auto& i : dat) for(auto& j : i) j *= a;
        return *this;
    }

    Matrix& operator+=(T a) {
        for(auto& i : dat) for(auto& j : i) j += a;
        return *this;
    }

    Matrix operator*(const Matrix& a) const { Matrix res(*this); return res *= a; }
    Matrix operator+(const Matrix& a) const { Matrix res(*this); return res += a; }
    Matrix& operator-=(const Matrix& a) { return *this += -a; }
    Matrix operator-(const Matrix& a) const { Matrix res(*this); return res -= a; }

    Matrix operator*(T a) const { Matrix res(*this); return res *= a; }
    Matrix operator+(T a) const { Matrix res(*this); return res += a; }
    Matrix& operator-=(T a) { return *this += -a; }
    Matrix operator-(T a) const { Matrix res(*this); return res -= a; }

    const vector<T>& operator[](size_t i) const { return dat[i]; };
    vector<T>& operator[](size_t i) { return dat[i]; };

    const Matrix pow(long long k) const{
        assert(n == m);
        Matrix res(n, m);
        if(k == 0) {
            for(int i = 0; i < n; ++i) res[i][i] = 1;
            return res;
        }
        res = pow(k >> 1);
        res *= res;
        if(k & 1) res *= *this;
        return res;
    }

    friend ostream& operator<<(std::ostream& s, const Matrix& a) {
        for(int i = 0; i < a.n; ++i) {
            for(int j = 0; j < a.m; ++j) s << a[i][j] << ' ';
            if(i < a.n - 1) s << endl;
        }
        return s;
    }
};

int main() {
    using T = mint;
    vector<vector<T>> b({{-2}, {3}});
    Matrix<T> ma({{1, 2}, {3, 4}});
    Matrix<T> mb(b);
    Matrix<T> mc = ma * 3;
    cout << mc << endl;
}