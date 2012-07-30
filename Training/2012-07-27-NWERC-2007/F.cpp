
//coding
//15:10
//--15:24
//15:30
//--16:10
//total 54min

//debuging
//16:14
//--16:54
//total 40min

//redebuging
//16:56
//--17:00

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

#define sq(x) ((x) * (x))

const int MaxN = 20 + 5, MaxC = 20 + 5, MaxM = 30 + 5;
const double eps = 1e-9;

int T, C, N, Tot;

struct Point {
	double x, y;
	Point() {}
	Point(double _x, double _y): x(_x), y(_y) {}
	void load() {
		scanf("%lf%lf", &x, &y);
	}
	Point operator + (const Point &t) const {
		return Point(x + t.x, y + t.y);
	}
	Point operator - (const Point &t) const {
		return Point(x - t.x, y - t.y);
	}
	Point operator * (const double t) const {
		return Point(x * t, y * t);
	}
	Point operator / (const double t) const {
		return Point(x / t, y / t);
	}
	bool operator < (const Point &t) const {
		if (fabs(x - t.x) < eps) return y < t.y;
		return x < t.x;
	}
	Point turnClockwise() {
		return Point(y, -x);	
	}
	double mo() {
		return sqrt(sq(x) + sq(y));
	}
	double dis(const Point &t) const {
		return sqrt(sq(x - t.x) + sq(y - t.y));
	}
	Point normalize() {
		return *this / mo();
	}
	double det(const Point &t) const {
		return x * t.y - y * t.x;
	}
	void out() const {
		printf("%lf %lf\n", x, y);
	}
}route[MaxN], continent[MaxC][MaxM], poly[MaxC + MaxC * MaxM][MaxM];
int num[MaxC], sz[MaxC + MaxC * MaxM];

struct Circle {
	Point o; double r;
	Circle() {}
	Circle(Point _o, double _r): o(_o), r(_r) {}
}circle[MaxC][MaxM];

struct Seg {
	Point a, b;
	Seg() {}
	Seg(Point _a, Point _b): a(_a), b(_b) {}
	bool hasInter(const Seg &t) const {
		return (b - a).det(t.a - a) * (b - a).det(t.b - a) < 0 
			&& (t.b - t.a).det(a - t.a) * (t.b - t.a).det(b - t.a) < 0;
	}
	Point intersect(const Seg &t) const {
		double t1 = (b - a).det(t.a - a), t2 = -(b - a).det(t.b - a);
		return (t.a * t2 + t.b * t1) / (t1 + t2);
	}
	void pushIntersection(const Circle O, vector<Point> &inters) const {
		double x0 = a.x - O.o.x, y0 = a.y - O.o.y, dx = b.x - a.x, dy = b.y - a.y;
		double A = sq(dx) + sq(dy), B = 2 * (x0 * dx + y0 * dy), C = sq(x0) + sq(y0) - sq(O.r);
		double delta = sq(B) - 4 * A * C;
		if (delta < eps) return;
		delta = sqrt(delta);
		double t1 = (-B + delta) / (2 * A);
		double t2 = (-B - delta) / (2 * A);
		if (t1 > 0 && t1 < 1) inters.push_back(Point(a.x + t1 * dx, a.y + t1 * dy));
		if (t2 > 0 && t2 < 1) inters.push_back(Point(a.x + t2 * dx, a.y + t2 * dy));
	}
};

bool nonZero(Point t) {
	return fabs(t.x) > eps || fabs(t.y) > eps;
}

double getArea(Point* pts, int N) {
	double res = 0;
	for (int i = 0; i < N; ++i) 
		res += pts[i].det(pts[i + 1]);
	return res;
}

void reverse(Point* pts, int N) {
	for (int i = 0; i < N - 1 - i; ++i) 
		swap(pts[i], pts[N - 1 - i]);
}

bool isInner(const Point &P, const Circle &O) {
	return P.dis(O.o) < O.r;
}

bool isInner(const Point &t, const Point* pts, int N) {
	int cnt = 0; Seg now(t, Point(1234567.8, 2345678.9));
	for (int i = 0; i < N; ++i) 
		if (now.hasInter(Seg(pts[i], pts[i + 1]))) cnt++;
	return (cnt & 1);
}

vector<Point> inters;

typedef pair<Point, Point> pii;

vector<pii> segs;

bool recheck(Point a, Point b) {
	if (b < a) swap(a, b);
	Seg now(a, b); segs.clear();
	for (int i = 0; i < Tot; ++i) {
		inters.clear(); inters.push_back(a); inters.push_back(b);
		for (int j = 0; j < sz[i]; ++j) {
			if (now.hasInter(Seg(poly[i][j], poly[i][j + 1]))) 
				inters.push_back(now.intersect(Seg(poly[i][j], poly[i][j + 1])));
		}
		sort(inters.begin(), inters.end());	
		for (int k = 0; k + 1 < (int)inters.size(); ++k) if (nonZero(inters[k] - inters[k + 1])) {
			Point mid = (inters[k] + inters[k + 1]) / 2;
			if (isInner(mid, poly[i], sz[i])) segs.push_back(pii(inters[k], inters[k + 1]));
		}
	}
	for (int i = 0; i < C; ++i) 
		for (int j = 0; j < num[i]; ++j) {
			inters.clear(); inters.push_back(a); inters.push_back(b);
			now.pushIntersection(circle[i][j], inters);
			sort(inters.begin(), inters.end());	
			for (int k = 0; k + 1 < (int)inters.size(); ++k) if (nonZero(inters[k] - inters[k + 1])) {
				Point mid = (inters[k] + inters[k + 1]) / 2;
				if (isInner(mid, circle[i][j])) segs.push_back(pii(inters[k], inters[k + 1]));
			}
		}
	sort(segs.begin(), segs.end());
	Point last = a;
	for (int i = 0; i < (int)segs.size(); ++i) {
		if (last < segs[i].first) return true;	
		last = max(last, segs[i].second);
	}
	if (last < b) return true;
	return false;
}

bool check(double d) {
	for (int i = 0; i < C; ++i) {
		sz[i] = 0;
		for (int j = 0; j < num[i]; ++j) {
			circle[i][j] = Circle(continent[i][j], d);
			poly[i][sz[i]++] = continent[i][j];
		}
		poly[i][sz[i]] = poly[i][0];
	}
	Tot = C;
	for (int i = 0; i < C; ++i) {
		for (int j = 0; j < num[i]; ++j) {
			Point dir = (continent[i][j + 1] - continent[i][j]).turnClockwise().normalize() * d;
			Point p1 = continent[i][j] + dir;
			Point p2 = continent[i][j + 1] + dir;
		    sz[Tot] = 4;
			poly[Tot][0] = continent[i][j]; poly[Tot][1] = p1;
			poly[Tot][2] = p2; poly[Tot][3] = continent[i][j + 1];
			poly[Tot][4] = poly[Tot][0];
			Tot++;
		}
	}
	for (int i = 0; i + 1 < N; ++i) {
		if (recheck(route[i], route[i + 1])) return true;	
	}
	return false;	
}

int main() {

   	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &C, &N);
		for (int i = 0; i < N; ++i) route[i].load();
		for (int i = 0; i < C; ++i) {
			scanf("%d", num + i);
			for (int k = 0; k < num[i]; ++k) {
				continent[i][k].load();
			}
			continent[i][num[i]] = continent[i][0];
			if (getArea(continent[i], num[i]) < 0) 
				reverse(continent[i], num[i]);
			continent[i][num[i]] = continent[i][0];
		}
		double L = 0, R = 1e5, Mid;
		for (int rep = 0; rep <= 50; ++rep) {
			Mid = (L + R) / 2;
			if (check(Mid)) L = Mid;
			else R = Mid;
		}
		printf("%.6f\n", (L + R) / 2);
	}

    return 0;

}

