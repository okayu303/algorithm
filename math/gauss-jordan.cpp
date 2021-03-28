#include <bits/stdc++.h>
using namespace std;

constexpr long double EPS = 1e-12;

// Ax=bを解く。Aは正方行列
// 解がない又は一意でない場合は長さ0の配列を返す
using vec = vector<long double>;
using mat = vector<vec>;
vec gause_jordan(const mat& A, const vec& b) {
    int n = A.size();

    // 行列Aの後ろにbを並べる
    mat B(n, vec(n+1));
    for(int i = 0; i < n; ++i) for(int j = 0; j < n; ++j) B[i][j] = A[i][j];
    for(int i = 0; i < n; ++i) B[i][n] = b[i];

    for(int j = 0; j < n; ++j) {    // 左の列から見ていく
        // (j,j)の係数の絶対値を最大にする
        int pivot = j;
        for(int i = j; i < n; ++i) {
            if(abs(B[i][j]) > abs(B[pivot][j])) pivot = i;
        }
        swap(B[j], B[pivot]);

        // rank(A)=nではないので解なし
        if(abs(B[j][j]) < EPS) return vec();

        // B(j,j)の係数を1にするのに伴い(j+1)列目以降を割る。B(j,j)自体は今後見ないので割らなくて良い
        for(int k = j+1; k <= n; ++k) B[j][k] /= B[j][j];

        // B(j+x,j)の係数を0にする。B(j+x,j)自体は今後見ないので0にしなくて良い
        for(int i = 0; i < n; ++i) {
            if(i == j) continue;
            // B[j]の行全体を先頭の係数B[i][j]で掛けて、B[i]の行全体から引く
            for(int k = j+1; k <= n; ++k) B[i][k] -= B[i][j] * B[j][k];
        }
    }
    vec x(n);
    for(int i = 0; i < n; ++i) x[i] = B[i][n];
    return x;
}

int main() {
    cout << fixed << setprecision(5);
    mat A = {{1, -2, 3}, {4, -5, 6}, {7, -8, 10}};
    vec b = {6, 12, 21};
    vec x = gause_jordan(A, b);
    for(auto i : x) cout << i << endl;
}