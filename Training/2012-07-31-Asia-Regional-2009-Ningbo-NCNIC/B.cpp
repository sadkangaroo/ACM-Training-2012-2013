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

const int MaxN = 16, MaxM = 16;
const int MaxNode = 100000, MaxR = 10000, MaxC = 300;

int top;
vector<int> rr[MaxN], cc[MaxM], tmp, s;

void predfs(int now, int pos, int sta, int bound) {
	if (now == s.size()) {
		tmp.push_back(sta);
		return;
	}
	for (int i = pos; i + s[now] - 1 < bound; ++i) 
		predfs(now + 1, i + s[now] + 1, sta | (((1 << s[now]) - 1) << i), bound);
}

void load(int bound) {
	s.clear(); int x;	
	while (scanf("%d", &x) && x) s.push_back(x);
	tmp.clear();
	predfs(0, 0, 0, bound);
}

int N, M, h, buf, ans;
int lx[MaxR][MaxC], ly[MaxC][MaxR], plx[MaxR], ply[MaxC], O[MaxR];
int L[MaxNode], R[MaxNode], U[MaxNode], D[MaxNode], C[MaxNode], row[MaxNode];

void remove(int c) {
    L[R[c]] = L[c]; R[L[c]] = R[c];
    for (int x = D[c]; x != c; x = D[x])
        for (int y = R[x]; y != x; y = R[y]) 
            U[D[y]] = U[y], D[U[y]] = D[y], ply[C[y]]--;
}

void resume(int c) {
    for (int x = U[c]; x != c; x = U[x])
        for (int y = L[x]; y != x; y = L[y]) 
            U[D[y]] = y, D[U[y]] = y, ply[C[y]]++;
    L[R[c]] = c; R[L[c]] = c;
}

const int oo = 0x3f3f3f3f;

bool dfs(int k) {
    if (R[h] == h) {ans = k - 1; return true;}
    int s = oo, c;
    for (int y = R[h]; y != h; y = R[y])
        if (ply[y] < s) s = ply[y], c = y;
    remove(c);
    for (int x = D[c]; x != c; x = D[x]) {
        O[k] = row[x];
        for (int y = R[x]; y != x; y = R[y]) remove(C[y]);
        if (dfs(k + 1)) return true;
        for (int y = L[x]; y != x; y = L[y]) resume(C[y]);
    }
    resume(c);
    return false;
}

bool flag[MaxR];

void solve() {
    h = ans = 0;
	memset(flag, false, sizeof(flag));
	dfs(1);
    for (int i = 1; i <= ans; ++i)
		flag[O[i]] = true;
}

void reset(int M) {
	buf = M;
    memset(plx, 0, sizeof(plx));
    memset(ply, 0, sizeof(ply));
}

void addNode(int x, int y) {
	lx[x][plx[x]++] = ly[y][ply[y]++] = ++buf;
	C[buf] = y; row[buf] = x;
}

void DLX(int N, int M) {
    int a, b;
    for (int x = 1; x <= N; ++x)
        for (int k = 0; k < plx[x]; ++k) {
            a = lx[x][k]; b = lx[x][(k + 1) % plx[x]];
            R[a] = b; L[b] = a;
        }
    for (int y = 0; y <= M; ++y) {
        R[y] = (y + 1) % (M + 1); 
        L[(y + 1) % (M + 1)] = y;
    }
    for (int y = 1; y <= M; ++y) {
        for (int k = 0; k < ply[y] - 1; ++k) {
            a = ly[y][k]; b = ly[y][k + 1];
            D[a] = b; U[b] = a;
        }
        if (ply[y]) {
            U[ly[y][0]] = y; D[y] = ly[y][0];
            D[ly[y][ply[y] - 1]] = y; U[y] = ly[y][ply[y] - 1];
        }
        else D[y] = U[y] = y;
    }           
	solve();
}

void Println(int x, int M) {
	for (int i = 0; i < M; ++i) 
		if ((x >> i) & 1) putchar('*');
		else putchar('.');
	puts("");
}

#define lab(x, y) ((x) * M + (y))

int main() {

	int N, M;
   	while (scanf("%d%d", &N, &M) && (N || M)) {
		for (int i = 0; i < N; ++i) {
			load(M); rr[i] = tmp;
		}
		for (int i = 0; i < M; ++i) {
			load(N); cc[i] = tmp;
		}
		reset(N * M + N + M);
		top = 0;
		for (int i = 0; i < N; ++i) {
			for (int k = 0; k < rr[i].size(); ++k) {
				top++;
				addNode(top, i + 1);
				for (int v = 0; v < M; ++v) {
					if ((rr[i][k] >> v) & 1)
						addNode(top, N + M + lab(i, v) + 1);
				}
			}
		}
		for (int i = 0; i < M; ++i) {
			for (int k = 0; k < cc[i].size(); ++k) {
				top++;
				addNode(top, N + i + 1);
				for (int v = 0; v < N; ++v) {
					if (((cc[i][k] >> v) & 1) ^ 1) 
						addNode(top, N + M + lab(v, i) + 1);
				}
			}
		}
		DLX(top, N + M + N * M);
		top = 0;
		for (int i = 0; i < N; ++i) {
			for (int k = 0; k < rr[i].size(); ++k) {
				top++;
				if (flag[top]) {
					Println(rr[i][k], M);
				}
			}
		}
		puts("");
	}

    return 0;

}

