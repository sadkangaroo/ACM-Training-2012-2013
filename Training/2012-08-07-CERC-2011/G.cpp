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

const int MaxN = 100 + 5, MaxM = 100 + 5;
const int dx[4] = {0, 1, -1, 0};
const int dy[4] = {1, 0, 0, -1};

int N, M;
char a[MaxN][MaxM];
bool vis[MaxN][MaxM];
int match[MaxN][MaxM];

bool find(int nx, int ny) {
	for (int k = 0; k < 4; ++k) {
		int tx = nx + dx[k], ty = ny + dy[k];
		if (a[tx][ty] != 'X' && !vis[tx][ty]) {
			vis[tx][ty] = true;
			int kk = match[tx][ty];
			if (kk == -1 || find(tx + dx[kk], ty + dy[kk])) {
				match[nx][ny] = k; match[tx][ty] = 3 - k;
				return true;
			}
		}
	} return false;
}

bool existPath(int nx, int ny) {
	for (int k = 0; k < 4; ++k) {
		int tx = nx + dx[k], ty = ny + dy[k];
		if (a[tx][ty] != 'X' && !vis[tx][ty]) {
			vis[tx][ty] = true;
			int kk = match[tx][ty];
			if (kk == -1 || existPath(tx + dx[kk], ty + dy[kk])) return true;
		}
	}
	return false;
}

int main() {

   	while (scanf("%d%d ", &N, &M) && (N || M)) {
		for (int i = 1; i <= N; ++i) gets(a[i] + 1);		
		for (int i = 0; i <= N + 1; ++i) for (int j = 0; j <= M + 1; ++j)
			if (i == 0 || i == N + 1 || j == 0 || j == M + 1) a[i][j] = 'X';
		memset(match, -1, sizeof(match));
		int tmp = 0;
		for (int i = 1; i <= N; ++i) 
			for (int j = 1; j <= M; ++j)
				if (a[i][j] != 'X' && ((i + j) & 1) && match[i][j] == -1) { 
					memset(vis, false, sizeof(vis));
					if (find(i, j)) tmp++;
				}
		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= M; ++j) 
				if (a[i][j] == 'X') putchar('X');
				else {
					if (match[i][j] == -1) putchar('B');
					else {
						memset(vis, false, sizeof(vis));
						int kk = match[i][j];
						vis[i][j] = true;
						if (existPath(i + dx[kk], j + dy[kk])) putchar('B');
						else putchar('A');
					}
				}
			puts("");
		}
		puts("");
	}

    return 0;

}

