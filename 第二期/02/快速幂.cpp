#include <bits/stdc++.h>
using namespace std;
int main() {
	auto qpow = [&](int a, int b) -> int { // a ^ b
		int res = 1;
		while (b) {
			if(b & 1) res = res * a;
			a = a * a;
			b >>= 1;
		}
		return res;
	};
}
