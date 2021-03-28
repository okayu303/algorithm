#include <iostream>
#include <vector>
using namespace std;

struct BIT {    // 0-indexed
    int n;
    vector<long long> bit;

    BIT(int n) : n(n), bit(n + 1, 0) {}

    void add(int i, long long val){
        for(int x = i+1; x <= n; x += x & -x) bit[x] += val;
    }

    long long sum(int i){ // sum of [0, i)
        int ret = 0;
        for(int x = i; x > 0; x -= x &- x) ret += bit[x];
        return ret;
    }

    long long sum(int l, int r) {  // sum of [l, r)
        return sum(r) - sum(l);
    }

    long long get(int i) {
        return sum(i + 1) - sum(i);
    }

    void set(int i, long long val) {
        long long cur = get(i);
        if(val != cur) add(i, val - cur);
    }
};

int main() {
    BIT bit(10);
    for(int i = 0; i < 10; ++i) {
        bit.set(i, i+1);
    }
    cout << bit.sum(0, 8) << endl;
    for(int i = 0; i < 10; ++i) {
        cout << bit.get(i) << ' ';
    }
    cout << endl;
    bit.add(4, 5);
    for(int i = 0; i < 10; ++i) {
        cout << bit.get(i) << ' ';
    }
    cout << endl;
}