#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// 桁数の計算
// k進数のnの桁数を返す
ll count_digit(ll n, ll k = 10) {
    ll ret = 0;
    while(n > 0) {
        ++ret;
        n /= k;
    }
    return ret;
}

int main() {
    ll n, k;
    cin >> n >> k;
    cout << count_digit(n, k) << endl;
}