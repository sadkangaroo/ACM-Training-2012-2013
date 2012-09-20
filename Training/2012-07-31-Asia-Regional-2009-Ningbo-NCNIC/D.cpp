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

const int MaxN = 50000 + 5;
const int block = 20;

vector<int> seg[MaxN / block + 5];

struct Window {
	int x1, y1, x2, y2, priority;
	void load(int _priority) {
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		swap(y1, y2);
		priority = _priority;
	}
	void getRecorded(int lab) {
		int l = x1 / block, r = x2 / block;
		for (int i = l; i <= r; ++i)
			seg[i].push_back(lab);
	}
	bool contains(int x, int y) {
		return x >= x1 && x <= x2 && y >= y1 && y <= y2;	
	}
}windows[MaxN];

int N, M;

void query(int now, int x, int y) {
	int highest = -1, lab;
	for (int i = 0; i < seg[now].size(); ++i) {
		int cnt = seg[now][i];
		if (windows[cnt].contains(x, y)) {
			if (windows[cnt].priority > highest) {
				highest = windows[cnt].priority;
				lab = cnt;
			}
		}
	}
	if (highest == -1) puts("0");
	else {
		printf("%d\n", lab);
		windows[lab].priority = ++N;
	}
}

int C, R;

int main() {

   	scanf("%d%d", &C, &R); 
	for (int i = 0; i <= C / block; ++i) seg[i].clear();
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i) {
		windows[i].load(i);
		windows[i].getRecorded(i);
	}
	scanf("%d", &M);
	while (M--) {
		int x, y;
		scanf("%d%d", &x, &y);
		query(x / block, x, y);
	}

    return 0;

}

