//coding
//12:35
//--13:09
//total 34min

//debuging
//13:11
//13:19
//total 8min


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

const int MaxR = 16, MaxC = 16;
const int seed = 999983;
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};

#define ok(x, y) ((x) >= 0 && (x) < R && (y) >= 0 && (y) < C)

bool flag;
int T, R, C, Sx, Sy, Tx, Ty, ans;
char a[MaxR][MaxC];

struct State {
	char a[MaxR][MaxC];
	int nx, ny, len, dis;
	bool gameOver() {
		return nx == Tx && ny == Ty;
	}
	LL getHash() {
		LL res = 0;
		for (int i = 0; i < R; ++i)
			for (int j = 0; j < C; ++j)
				res = res * seed + a[i][j];
		res = res * seed + nx; res = res * seed + ny;
		res = res * seed + len; return res;
	}
	bool isWater(int x1, int y1, int x2, int y2) {
		if (x1 > x2) swap(x1, x2);
		if (y1 > y2) swap(y1, y2);
		for (int i = x1; i <= x2; ++i)
			for (int j = y1; j <= y2; ++j)
				if (!ok(i, j) || a[i][j] != '.') return false;
		return true;
	}
	bool fill(int x1, int y1, int x2, int y2, char c) {
		if (x1 > x2) swap(x1, x2);
		if (y1 > y2) swap(y1, y2);
		for (int i = x1; i <= x2; ++i)
			for (int j = y1; j <= y2; ++j)
				a[i][j] = c;
	}
	bool isStump(int x, int y) {
		return ok(x, y) && a[x][y] == 'S';
	}
}S;

queue<State> Q;
set<LL> Set;

void scanMap() {
	for (int i = 0; i < R; ++i)
		for (int j = 0; j < C; ++j) {
			S.a[i][j] = a[i][j];
			if (a[i][j] == 'B') {
				Sx = i; Sy = j;
				S.a[i][j] = 'S';
			}
			if (a[i][j] == 'E') {
				Tx = i; Ty = j;
				S.a[i][j] = 'S';
			}
		}
	S.nx = Sx; S.ny = Sy;
	S.len = 0;
}

void pushBack(State &now) {
	if (now.gameOver()) {flag = true; ans = now.dis;}
	LL hashcode = now.getHash();
	if (Set.count(hashcode)) return;
	Set.insert(hashcode);
	Q.push(now);
}

void go(State now, int d) {
	int tx = now.nx, ty = now.ny, len = 0; char c;
	if (d < 2) c = '-'; else c = '|';
	while (ok(tx + dx[d], ty + dy[d]) && now.a[tx + dx[d]][ty + dy[d]] == c) {
		tx += dx[d]; ty += dy[d];
		len++;
	}
	int nx = tx + dx[d], ny = ty + dy[d];
	if (len && ok(nx, ny) && now.a[nx][ny] == 'S') {
		now.nx = nx; now.ny = ny; now.dis++;
		pushBack(now);	
	}
}

void lay(State now, int d) {
	int len = now.len, nx = now.nx, ny = now.ny; char c;
	if (d < 2) c = '-'; else c = '|';
	if (now.isWater(nx + dx[d], ny + dy[d], nx + len * dx[d], ny + len * dy[d]) 
			&& now.isStump(nx + dx[d] * (len + 1), ny + dy[d] * (len + 1))) {
		now.fill(nx + dx[d], ny + dy[d], nx + len * dx[d], ny + len * dy[d], c);
		now.len = 0; now.dis++;
		pushBack(now);
	}
}

void pick(State now, int d) {
	int tx = now.nx, nx = tx, ty = now.ny, ny = ty, len = 0; char c;
	if (d < 2) c = '-'; else c = '|';
	while (ok(tx + dx[d], ty + dy[d]) && now.a[tx + dx[d]][ty + dy[d]] == c) {
		tx += dx[d]; ty += dy[d];
		len++;
	}
	int vx = tx + dx[d], vy = ty + dy[d];
	if (len && ok(vx, vy) && now.a[vx][vy] == 'S') {
		now.fill(nx + dx[d], ny + dy[d], tx, ty, '.');
		now.len = len; now.dis++;
		pushBack(now);	
	}
}

void bfs() {
	flag = false;
	while (!Q.empty()) Q.pop(); Q.push(S);
	Set.clear(); Set.insert(S.getHash());
	while (!Q.empty()) {
		if (flag) break;
		State now = Q.front(); Q.pop();
		for (int i = 0; i < 4; ++i) go(now, i);		
		if (now.len) {
			for (int i = 0; i < 4; ++i) lay(now, i);
		}
		else for (int i = 0; i < 4; ++i) pick(now, i);
	}
	if (flag) printf("%d\n", ans);
	else puts("0");
}

int main() {

   	scanf("%d", &T); 
	while (T--) {
		scanf("%d%d ", &R, &C);
		for (int i = 0; i < R; ++i) 
			gets(a[i]);
		scanMap();
		bfs();
	}

    return 0;

}

