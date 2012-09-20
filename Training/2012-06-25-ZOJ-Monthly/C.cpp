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

const int MaxN = 200 + 5, MaxM = 5000 + 5;
const int MaxSta = (1 << 8) + 5;

struct etp {
	int t, c; etp* nxt;
	etp() {}
	etp(int _t, int _c, etp* _nxt): t(_t), c(_c), nxt(_nxt) {}
}*e[MaxN], buf[MaxM * 2], *cbuf = buf;

void Me(int a, int b, int c) {
	e[a] = new(cbuf++)etp(b, c, e[a]);
	e[b] = new(cbuf++)etp(a, c, e[b]);
}

int N, M;
int P[MaxN], S[MaxN], key[8], dp[MaxN][MaxSta], top;

bool updateMin(int &a, int b) {
	if (a == -1 || b < a) {
		a = b; return true;
	} return false;
}

typedef pair<int, int> pii;
queue<pii> Q;

bool vis[MaxN][MaxSta];
int f[MaxSta];

void spfa() {
	while (!Q.empty()) {
		pii now = Q.front(); Q.pop();	
		int ni = now.first, nsta = now.second;
		for (etp* u = e[ni]; u; u = u->nxt) if (updateMin(dp[u->t][nsta], dp[ni][nsta] + u->c)) {
			if (!vis[u->t][nsta]) {
				vis[u->t][nsta] = true;	
				Q.push(pii(u->t, nsta));
			}
		}
	}
}

int getResource(int sta) {
	int res = 0;
	for (int i = 0; i < top; ++i)
		if ((sta >> i) & 1) if (S[key[i]]) res++;
	return res;
}

int getFactory(int sta) {
	int res = 0;	
	for (int i = 0; i < top; ++i)
		if ((sta >> i) & 1) res += P[key[i]];
	return res;
}

bool check(int sta) {
	return getResource(sta) <= getFactory(sta);
}

void solve() {
	memset(dp, -1, sizeof(dp));
	for (int i = 0; i < top; ++i) dp[key[i]][1 << i] = 0;
	for (int sta = 0; sta < (1 << top); ++sta) {
		while (!Q.empty()) Q.pop();
		memset(vis, false, sizeof(vis));
		for (int i = 0; i < N; ++i) {
			for (int sub = (sta - 1) & sta; sub; sub = (sub - 1) & sta) {
				if (dp[i][sub] != -1 && dp[i][sta - sub] != -1)
					updateMin(dp[i][sta], dp[i][sub] + dp[i][sta - sub]);
			}
			if (dp[i][sta] != -1) {
				Q.push(pii(i, sta));
				vis[i][sta] = true;
			}
		}
		spfa();
	}
	memset(f, -1, sizeof(f));
	for (int i = 0; i < N; ++i)
		for (int sta = 0; sta < (1 << top); ++sta)
			if (dp[i][sta] != -1 && check(sta)) updateMin(f[sta], dp[i][sta]);
	for (int sta = 0; sta < (1 << top); ++sta)
		for (int sub = (sta - 1) & sta; sub; sub = (sub - 1) & sta) {
			if (f[sub] != -1 && f[sta - sub] != -1)
				updateMin(f[sta], f[sub] + f[sta - sub]);
		}
	int ansNum = -1, ansMoney = -1;
	for (int sta = 0; sta < (1 << top); ++sta) {
		if (f[sta] != -1) {
			if (getResource(sta) > ansNum) {
				ansNum = getResource(sta);
				ansMoney = f[sta];
			}
			else if (getResource(sta) == ansNum)
				updateMin(ansMoney, f[sta]);
		}
	}
	printf("%d %d\n", ansNum, ansMoney);
}


int main() {

   	while (scanf("%d", &N) != -1) {
		memset(e, 0, sizeof(e)); cbuf = buf;
		top = 0;
		for (int i = 0; i < N; ++i) {
			scanf("%d%d", P + i, S + i);	
			if (P[i] || S[i]) {
				key[top++] = i;
			}
		}
		scanf("%d", &M);
		for (int i = 0; i < M; ++i) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			Me(a - 1, b - 1, c);
		}
		solve();
	}

    return 0;

}

