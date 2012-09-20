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

const int MaxN = 11, MaxM = 500 + 5;
const int MaxNode = 70000 + 5, MaxPts = 1000 + 5;
const int MaxLen = 50000 + 5;

struct Node {
	int mask; bool forbidden; Node *nxt, *c[2];
	Node(): mask(0), forbidden(false) {
		c[0] = c[1] = 0; nxt = this;
	}
}buf[MaxNode], *cbuf, *root;

int N, M;
char s[MaxLen];

void insert(char *s, int flag) {
	Node* now = root;
	for (int i = 0; s[i]; ++i) {
		if (now->c[s[i] - '0']) now = now->c[s[i] - '0'];
		else now = now->c[s[i] - '0'] = new(cbuf++)Node();
	} 
	if (flag == -1) now->forbidden = true;
	else now->mask |= (1 << flag);
}

queue<Node*> Q;

void getNext() {
	while (!Q.empty()) Q.pop(); Q.push(root);
	while (!Q.empty()) {
		Node* u = Q.front(); Q.pop();
		for (int i = 0; i < 2; ++i) { 
			if (u->c[i]) {
				Q.push(u->c[i]); 
				if (u == root) u->c[i]->nxt = root;
				else u->c[i]->nxt = u->nxt->c[i];
				u->c[i]->mask |= u->c[i]->nxt->mask;
				u->c[i]->forbidden |= u->c[i]->nxt->forbidden;
			}
			else {
				if (u == root) u->c[i] = root;
				else u->c[i] = u->nxt->c[i];
			}
		}
	}
}

vector<int> nds;
int dis[MaxNode], go[MaxPts][MaxPts];

queue<int> que;

void bfs(int lab, int S) {
	while (!que.empty()) que.pop();
	que.push(S);
	memset(dis, 63, sizeof(dis)); dis[S] = 0;
	while (!que.empty()) {
		int now = que.front(); que.pop();
		for (int i = 0; i < 2; ++i) {
			int t = buf[now].c[i] - buf;
			if (buf[t].forbidden) continue;
			if (dis[now] + 1 < dis[t]) {
				dis[t] = dis[now] + 1;
				que.push(t);
			}
		}
	}
	for (int i = 0; i < nds.size(); ++i)
		go[lab][i] = dis[nds[i]];
}

typedef pair<int, int> pii;

queue<pii> Que;
bool vis[MaxPts][1 << MaxN];
int dp[MaxPts][1 << MaxN];

void spfa() {
	int N = nds.size();
	while (!Que.empty()) Que.pop(); Que.push(pii(0, 0));
	memset(dp, 63, sizeof(dp)); dp[0][0] = 0;
	memset(vis, false, sizeof(vis)); vis[0][0] = true;
	while (!Que.empty()) {
		pii now = Que.front(); Que.pop(); int npos = now.first, nsta = now.second;
		vis[npos][nsta] = false;
		for (int i = 0; i < N; ++i) {
			int t = nsta | buf[nds[i]].mask;
			if (dp[npos][nsta] + go[npos][i] < dp[i][t]) {
				dp[i][t] = dp[npos][nsta] + go[npos][i];
				if (!vis[i][t]) {
					vis[i][t] = true;
					Que.push(pii(i, t));
				}
			}
		}
	}
}

const int oo = 0x3f3f3f3f;

void solve() {
	nds.clear();
	for (int i = 0; i < cbuf - buf; ++i) 
		if (i == 0 || buf[i].mask && !buf[i].forbidden) 
			nds.push_back(i);	
	for (int i = 0; i < nds.size(); ++i) 
		bfs(i, nds[i]);	
	spfa();
	int ans = oo;
	for (int i = 0; i < nds.size(); ++i) ans = min(ans, dp[i][(1 << N) - 1]); 
	printf("%d\n", ans);
}

int main() {

	while (scanf("%d%d ", &N, &M) && (N || M)) {
		cbuf = buf; root = new(cbuf++)Node();
		for (int i = 0; i < N; ++i) {
			gets(s);
			insert(s, i);
		}
		for (int i = 0; i < M; ++i) {
			gets(s);
			insert(s, -1);
		}
		getNext();
		solve();
	}

    return 0;

}

