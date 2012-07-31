#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<string>
#include<cctype>
#include<climits>
#include<algorithm>
#include<complex>
#include<vector>
#include<queue>
#include<set>
#include<map>

using namespace std;

typedef long long LL;

const int MaxLen = 100 + 5;

int Power(int a, int b, int Mod) {
	int res = 1;
	while (b) {
		if (b & 1) res = (LL)res * a % Mod;	
		b >>= 1;
		a = (LL)a * a % Mod;
	}
	return res;
}

struct CRT {
	int n, p[MaxLen], q[MaxLen], tmp[MaxLen], tq[MaxLen], now[MaxLen], R[MaxLen];
	void decompose(int x) {
		n = 0;
		for (int i = 2; i * i <= x; ++i) {
			if (x % i == 0) {
				p[n] = i; q[n] = 0; tmp[n] = 1;
				while (x % i == 0) {
					q[n]++;
					tmp[n] *= i;
					x /= i;
				} n++;
			}
		}
		if (x > 1) {
			p[n] = x; tmp[n] = x; q[n++] = 1;
		}
	}
	void reset() {
		for (int i = 0; i < n; ++i) {
			now[i] = 1;
			R[i] = tq[i] = 0;
		}
	}
	void multiply(int _x) {
		for (int i = 0; i < n; ++i) {
			int x = _x;
			while (x % p[i] == 0) {
				x /= p[i];
				tq[i]++;
			}
			now[i] = (LL)now[i] * x % tmp[i];
		}
	}
	void divide(int _x) {
		for (int i = 0; i < n; ++i) {
			int x = _x;
			while (x % p[i] == 0) {
				x /= p[i];
				tq[i]--;
			}
			int phi = tmp[i] / p[i] * (p[i] - 1);
			int t = now[i] = (LL)now[i] * Power(x, phi - 1, tmp[i]) % tmp[i];
			if (tq[i] < q[i]) {
				for (int k = 1; k <= tq[i]; ++k) t = t * p[i] % tmp[i];
				R[i] = (R[i] + t) % tmp[i];
			}
		}
	}
	int unite(int M) {
		int res; 
		for (int i = 0; i < n; ++i) {
			int phi = tmp[i] / p[i] * (p[i] - 1);
			int Mi = M / tmp[i];
			int inv = Power(Mi, phi - 1, tmp[i]);
			res = (res + (LL)R[i] * Mi % M * inv % M) % M;
		}
		return res;
	}
}crt;

int N, Mod;

int main() {

   	while (scanf("%d%d", &N, &Mod) && (N || Mod)) {
		if (Mod == 1) {
			puts("0");
			continue;
		}
		crt.decompose(Mod);			
		crt.reset();	
		for (int i = 1; i <= N; ++i) {
			crt.multiply(4 * i - 2);
			crt.divide(i + 1);
		}
		printf("%d\n", crt.unite(Mod));
	}

    return 0;

}

