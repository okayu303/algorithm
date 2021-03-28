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

// スターリング数をDPで求める
// n個のボールをk個の区別しない箱に1つ以上入れる場合の数（n個のボールをkのグループに分ける）
vector<vector<mint>> stirling(int n, int k) {
    vector<vector<mint>> res(n+1, vector<mint>(k+1));
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= k; ++j) {
            if(i < j) continue; // 空のグループは存在しない
            else if(i == j) res[i][j] = 1;  // 各グループにボールは1つ
            else {
                res[i][j] = res[i-1][j-1];  // ボール1が単独のグループ
                res[i][j] += res[i-1][j]*j; // ボール1以外のボールがj個のグループを形成。j個のグループのどれかにボール1を追加
            }
        }
    }
    return res;
}

// https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/5/DPL_5_I
int main() {
    int n, k;
    cin >> n >> k;
    vector<vector<mint>> S = stirling(n, k);
    cout << S[n][k] << endl;
    return;
}