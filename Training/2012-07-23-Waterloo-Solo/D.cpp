#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
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

const int MaxN = 150 + 5;
const int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};
const int oo = 0x3f3f3f3f;

int N, T, phase;
int upgrade[2][2], hits[MaxN][MaxN], v[MaxN][MaxN], vattack[MaxN][MaxN], dis[2][MaxN][MaxN];
bool vis[MaxN][MaxN], attack[MaxN][MaxN];
char a[MaxN][MaxN];

#define isArmy(x) ((x) == '1' || (x) == '2')
#define isEnermy(x, y) ((x) == '1' && (y) == '2' || (x) == '2' && (y) == '1')

struct Node {
	int x, y;
	Node() {}
	Node(int _x, int _y): x(_x), y(_y) {}
}Q[MaxN * MaxN]; int head, tail;

void bfs(char typ, int lab) {
	head = tail = 0;	
	memset(dis[lab], 63, sizeof(dis[lab]));
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= N; ++j)
			if (a[i][j] == typ) {
				Q[tail++] = Node(i, j);
				dis[lab][i][j] = 0;
			}
	while (head != tail) {
		Node now = Q[head++];
		int nx = now.x, ny = now.y;
		for (int dx = -1; dx <= 1; ++dx)
			for (int dy = -1; dy <= 1; ++dy)
				if (abs(dx + dy) == 1) {
					int tx = nx + dx, ty = ny + dy;
					if (a[tx][ty] != '#' && dis[lab][nx][ny] + 1 < dis[lab][tx][ty]) {
						dis[lab][tx][ty] = dis[lab][nx][ny] + 1;
						Q[tail++] = Node(tx, ty);
					}
				}
	}
}

vector<Node> move;

void go(int sx, int sy) {
	move.clear();
	int nx = sx, ny = sy;
	for (;;) {
		vis[nx][ny] = true;
		int k = v[nx][ny], tx = nx + dx[k], ty = ny + dy[k];
		if (isArmy(a[tx][ty]) && v[tx][ty] == -1) return;
		move.push_back(Node(nx, ny));
		nx = tx; ny = ty;
		if (a[nx][ny] == '.') break;
	}
	for (int i = (int)move.size() - 1; i >= 0; --i) {
		nx = move[i].x; ny = move[i].y;
		int k = v[nx][ny];
		int tx = nx + dx[k], ty = ny + dy[k];
		hits[tx][ty] = hits[nx][ny];
		a[tx][ty] = a[nx][ny];
		a[nx][ny] = '.';
		v[nx][ny] = -1;
	}
}

void conduct() {
	memset(vattack, -1, sizeof(vattack));
	memset(attack, false, sizeof(attack));
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= N; ++j)
			if (isArmy(a[i][j])) {
				for (int k = 0; k < 8; ++k) {
					int tx = i + dx[k], ty = j + dy[k];
					if (isEnermy(a[i][j], a[tx][ty])) {
						vattack[i][j] = k;
						attack[i][j] = true;
						break;
					}
				}
			}
	memset(v, -1, sizeof(v));
	memset(vis, false, sizeof(vis));
	bfs('1', 1); bfs('2', 0);
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= N; ++j)
			if (isArmy(a[i][j]) && !attack[i][j]) {
				int lab = a[i][j] - '1', MIN = oo;
				for (int k = 0; k < 8; ++k) {
					int tx = i + dx[k], ty = j + dy[k];
					if (dis[lab][tx][ty] < MIN) {
						MIN = dis[lab][tx][ty];
						v[i][j] = k;
					}
				}
				int k = v[i][j];
				if (vis[i + dx[k]][j + dy[k]]) v[i][j] = -1;
				else vis[i + dx[k]][j + dy[k]] = true;
			}
	for (int i = 1; i <= N; ++i) 
		for (int j = 1; j <= N; ++j) 
			if (vattack[i][j] != -1) {
				int k = vattack[i][j];
				int tx = i + dx[k], ty = j + dy[k];
				hits[tx][ty] -= max(0, 5 + upgrade[a[i][j] - '1'][0] - upgrade[a[tx][ty] - '1'][1]);
			}
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= N; ++j)
			if (isArmy(a[i][j]) && hits[i][j] <= 0) 
				a[i][j] = '.';
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= N; ++j)
			if (v[i][j] != -1 && !vis[i][j]) go(i, j);
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= N; ++j)
			if (isArmy(a[i][j]) && hits[i][j] < 35) hits[i][j]++;
}

int main() {

	bool isFirst = true;;
   	while (scanf("%d", &N) && N) {
		for (int i = 0; i < 2; ++i) for (int j = 0; j < 2; ++j)
			scanf("%d ", &upgrade[i][j]);
		for (int i = 1; i <= N; ++i) gets(a[i] + 1);
		for (int i = 0; i <= N + 1; ++i)
			for (int j = 0; j <= N + 1; ++j) {
				if (i == 0 || i == N + 1 || j == 0 || j == N + 1)
					a[i][j] = '#';
				hits[i][j] = 35;
			}
		scanf("%d", &T);
		for (phase = 1; phase <= T; ++phase) {
			conduct();
		}
		if (isFirst) isFirst = false;	
		else puts("");
		for (int i = 1; i <= N; ++i) {
			a[i][N + 1] = 0;					
			puts(a[i] + 1);
		}
	}

    return 0;

}

