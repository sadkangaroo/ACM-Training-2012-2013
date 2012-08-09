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

const int MaxN = 10;
const double eps = 1e-8;
const double pi = acos(-1.0);

#define sq(x) ((x) * (x))

struct Point {
	double x, y;
	Point() {}
	Point(double _x, double _y): x(_x), y(_y) {}
	void load() {
		cin >> x >> y;
	}
	Point operator + (const Point &t) const {
		return Point(x + t.x, y + t.y);
	}
	Point operator - (const Point &t) const {
		return Point(x - t.x, y - t.y);
	}
	Point operator * (const double &t) const {
		return Point(x * t, y * t);
	}
	Point operator / (const double &t) const {
		return Point(x / t, y / t);
	}
	double dis(const Point &t) const {
		return sqrt(sq(x - t.x) + sq(y - t.y));
	}
	double det(const Point &t) const {
		return x * t.y - y * t.x;
	}
	double dot(const Point &t) const {
		return x * t.x + y * t.y;
	}
	double mo() const {
		return sqrt(sq(x) + sq(y));
	}
	Point normalize() const {
		return *this / mo();
	}
	Point turn() const {
		return Point(-y, x);
	}
	void out() const {
		cout << x << ' ' << y << endl;
	}
};

struct Seg {
	Point a, b;
	Seg() {}
	Seg(Point _a, Point _b): a(_a), b(_b) {}
	void load() {
		a.load(); b.load();
	}
	Point getOpp(const Point &p) {
		double rate = (p - a).dot(b - a) / (b - a).dot(b - a);
		Point tmp = a + (b - a) * rate;
		return tmp * 2 - p;
	}
	bool hasInter(const Seg &t) const {
		return (b - a).det(t.a - a) * (b - a).det(t.b - a) < -eps
			&& (t.b - t.a).det(a - t.a) * (t.b - t.a).det(b - t.a) < -eps;
	}
	Point intersectWith(const Seg &t) const {
		double t1 = (b - a).det(t.a - a), t2 = -(b - a).det(t.b - a);
		return (t.a * t2 + t.b * t1) / (t1 + t2);
	}
	bool containsPoint(const Point &t) const {
		return (t - a).dot(t - b) < -eps;
	}
}segs[MaxN];

int rec[MaxN];
int N;
vector<int> ans;

int normalizedAng(double ang) {
	if (ang < 0) ang += 2 * pi;
	int tmp = (int)(ang / pi * 180 + 0.5);
	if (tmp < 0) tmp += 360;
	if (tmp >= 360) tmp -= 360;
	return tmp;
}

void recheck(Point dir, Point now, int tot) {
	Point _dir = dir;
	for (int i = tot - 1; i >= 0; --i) {
		Seg beam(now, now + dir);	
		Point cx = beam.intersectWith(segs[rec[i]]);
		if ((cx - now).dot(dir) < 0 || !segs[rec[i]].containsPoint(cx)) return;
		for (int k = 0; k < N; ++k) if (((i == tot - 1 || k != rec[i + 1]) && k != rec[i])) {
			if (Seg(now, cx).hasInter(segs[k])) return;
		}
		Point tmp = segs[rec[i]].getOpp(now);
		now = cx;
		dir = cx - tmp;
	}
	Seg vec(now, Point(0, 0));
	for (int k = 0; k < tot; ++k) if (k != rec[0]) 
		if (vec.hasInter(segs[k])) return;
	if (fabs((vec.b - vec.a).det(dir)) > eps || (vec.b - vec.a).dot(dir) < -eps) return;
	double ang = atan2(_dir.y, _dir.x);
	int tt = normalizedAng(ang);
	ans.push_back(normalizedAng(ang));
}

void check(int tot) {
	Point now(0, 0);	
	for (int i = 0; i < tot; ++i) {
		now = segs[rec[i]].getOpp(now);
	}
	Point dir = now;
	now = Point(0, 0);
	recheck(dir, now, tot);
}

void dfs(int now) {
	if (now == 7) {
		return;
	}
	for (int i = 0; i < N; ++i)
		if (now == 0 || i != rec[now - 1]) {
			rec[now] = i;
			check(now + 1);
			dfs(now + 1);
		}
}

int main() {

   	while (scanf("%d", &N) && N) {
		for (int i = 0; i < N; ++i) segs[i].load();
		ans.clear();
		dfs(0);	
		if ((int)ans.size() == 0) puts("no danger");
		else {
			sort(ans.begin(), ans.end());
			ans.resize(unique(ans.begin(), ans.end()) - ans.begin());
			int sz = (int)ans.size();
			for (int i = 0; i < sz; ++i) 
				if (i == sz - 1) printf("%d\n", ans[i]);
				else printf("%d ", ans[i]);
		}
	}

    return 0;

}

