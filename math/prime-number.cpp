#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

vector<ll> prime_number(ll max_n) {
	vector<bool> vb(max_n + 1, true);
	vb[0] = vb[1] = false;
	vector<ll> ret;
	for(ll i = 2; i <= max_n; i++) {
		if(!vb[i]) continue;
		for(ll j = 2 * i; j <= max_n; j += i) {
			vb[j] = false;
		}
	}
	for(ll i = 2; i <= max_n; i++) {
		if(vb[i]) ret.push_back(i);
	}
	return ret;
}

int main() {
	ll n;
	cin >> n;
	vector<ll> prime = prime_number(n);
	for(ll& i : prime) cout << i << endl;
}