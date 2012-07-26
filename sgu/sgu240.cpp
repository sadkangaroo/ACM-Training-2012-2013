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

const int MaxNode = 100 + 5, MaxE = 10000 * 2 + 5;
const int oo = 0x3f3f3f3f;

int N, M, H, S, E;
bool isExit[MaxNode];
vector<int> ans;

struct etp {
	int t, c, t0, v; etp* nxt;
	etp() {}
	etp(int _t, int _c, int _t0, int _v, etp* _nxt): t(_t), c(_c), t0(_t0), v(_v), nxt(_nxt) {}
}*e[MaxNode], buf[MaxE], *cbuf;

void Me(int a, int b, int c, int t0, int v) {
	e[a] = new(cbuf++)etp(b, c, t0, v, e[a]);
	e[b] = new(cbuf++)etp(a, c, t0, v, e[b]);
}

bool vis[MaxNode];
int dis[MaxNode], pre[MaxNode];
int Q[MaxNode], head, tail;

inline void rz(int &x) {
	if (x == MaxNode) x = 0;
}

void getAns(int now) {
	ans.clear();
	for (;;) {
		ans.push_back(now);
		if (now == S) break;
		now = pre[now];
	}
}

bool spfa(int Limit) {
	head = tail = 0;	
	Q[tail++] = S;
	memset(vis, false, sizeof(vis)); vis[S] = true;
	memset(dis, 63, sizeof(dis)); dis[S] = 0;
	while (head != tail) {
		int now = Q[head++]; rz(head); vis[now] = false;
		for (etp* u = e[now]; u; u = u->nxt) {
			if (u->t0 + (dis[now] + u->c) * u->v <= Limit && dis[now] + u->c < dis[u->t]) {
				dis[u->t] = dis[now] + u->c; pre[u->t] = now;
				if (!vis[u->t]) {
					vis[u->t] = true;
					Q[tail++] = u->t; rz(tail);
				}
			}
		}
	}
	for (int i = 1; i <= N; ++i) if (isExit[i] && dis[i] < oo) {
		getAns(i);
		return true;
	}
	return false;
}

int main() {

	cbuf = buf; memset(e, 0, sizeof(e));
   	scanf("%d%d%d%d%d", &N, &M, &H, &S, &E); 
	int a, b, t, r, p, x;
	for (int i = 0; i < M; ++i) {
		scanf("%d%d%d%d%d", &a, &b, &t, &r, &p);
		Me(a, b, t, r, p);
	}
	memset(isExit, false, sizeof(isExit));
	for (int i = 0; i < E; ++i) {
		scanf("%d", &x);
		isExit[x] = true;
	}
	int L = 0, R = H + 1, Mid;
	while (L != R) {
		int Mid = (L + R) >> 1;
		if (spfa(Mid)) R = Mid;
		else L = Mid + 1;
	}
	if (L > H) {
		puts("NO");
	}
	else {
		puts("YES");
		printf("%d\n", L);
		spfa(L);
		int sz = ans.size();
		printf("%d", sz);
		for (int i = sz - 1; i >= 0; --i) printf(" %d", ans[i]);
		puts("");
	}

    return 0;

}

