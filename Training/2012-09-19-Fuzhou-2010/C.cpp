#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<cctype>
#include<algorithm>

using namespace std;

const double eps = 1e-8;

struct point3 {
	double x, y, z;
	point3() {}
	point3(double _x, double _y, double _z): x(_x), y(_y), z(_z) {}
	void load() {
		scanf("%lf%lf%lf", &x, &y, &z);
	}
	point3 operator + (const point3 &t) const {
		return point3(x + t.x, y + t.y, z + t.z);
	}
	point3 operator - (const point3 &t) const {
		return point3(x - t.x, y - t.y, z - t.z);
	}
	point3 operator / (const double t) const {
		return point3(x / t, y / t, z / t);
	}
	point3 operator * (const double t) const {
		return point3(x * t, y * t, z * t);
	}
	double norm() const {
		return sqrt(x * x + y * y + z * z);
	}
	point3 normalize() const {
		return *this / norm();
	}
    void out() const {
        cout << x << ' ' << y << ' ' << z << endl;
    }
};

struct plane3 {
	point3 a, b, c;
	plane3() {}
	plane3(point3 _a, point3 _b, point3 _c): a(_a), b(_b), c(_c) {}
};

struct line3 {
	point3 a, b;
	line3() {}	
	line3(point3 _a, point3 _b): a(_a), b(_b) {}
};

point3 det(const point3 &a, const point3 &b) {
	return point3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

double dot(const point3 &a, const point3 &b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

point3 pvec(point3 a, point3 b, point3 c) {
	return det(a - b, b - c);
}

point3 pvec(plane3 pl) {
	return pvec(pl.a, pl.b, pl.c);
}

point3 intersection(line3 l, plane3 s) {
	point3 ret = pvec(s);
	double t = (ret.x * (s.a.x - l.a.x) + ret.y * (s.a.y - l.a.y) + ret.z * (s.a.z - l.a.z))
		/ (ret.x * (l.b.x - l.a.x) + ret.y * (l.b.y - l.a.y) + ret.z * (l.b.z - l.a.z));
	ret = l.a + (l.b - l.a) * t;
	return ret;
}

point3 getPoint(double a, double b, double c, double d) {
	if (fabs(b) < eps && fabs(c) < eps) {
		return point3(d / a, 0, 0);	
	}
	if (fabs(c) < eps) {
		return point3(0, d / b, 0);
	}
	return point3(0, 0, d / c);
}

point3 getVer(double a, double b, double c) {
    if (fabs(b) < eps && fabs(c) < eps) 
        return point3(b, -a, 0);
    else return point3(0, c, -b);
}

const int MaxN = 100 + 5;

struct Point {
	double x, y;
	Point() {}
	Point(double _x, double _y): x(_x), y(_y) {}
	bool operator < (const Point &t) const {
		if (fabs(y - t.y) < eps) return x < t.x;
		return y < t.y;
	}
	Point operator - (const Point &t) const {
		return Point(x - t.x, y - t.y);
	}
	double det(const Point &t) const {
		return x * t.y - y * t.x;
	}
};

int N, top;
double a, b, c, d;
point3 pts[MaxN], S, P, V, X, Y;
Point pp[MaxN], stk[MaxN];

Point get2DPoint(const point3 &cx) {
	return Point(dot(X, cx), dot(Y, cx));
}

double graham(Point* pts, int N) {
	sort(pts, pts + N);	
	int top = 0;
	for (int i = 0; i < N; ++i) {
		while (top >= 2 && (stk[top - 1] - stk[top - 2]).det(pts[i] - stk[top - 1]) > -eps) top--;
		stk[top++] = pts[i];
	}
	int base = top - 1;
	for (int i = N - 2; i >= 0; --i) {
		while (top - base >= 2 && (stk[top - 1] - stk[top - 2]).det(pts[i] - stk[top - 1]) > -eps) top--;
		stk[top++] = pts[i];
	}
	top--;
	double res = 0;
	for (int i = 0; i < top; ++i) 
		res += stk[i].det(stk[i + 1]);
	return fabs(res / 2);
}

void solve() {
	top = 0;
	for (int i = 0; i < N; ++i) {
		if (fabs(dot(pts[i] - S, V)) < eps) continue;
		point3 cx = intersection(line3(S, pts[i]), plane3(P, P + X, P + Y));
		if (dot(pts[i] - S, cx - S) < -eps) continue;
		pp[top++] = get2DPoint(cx - P);
	}
	if (top == 0) {
		puts("0.00"); return;
	}
	if (top != N) {
		puts("Infi"); return;
	}
	printf("%.2f\n", graham(pp, top));
}

int main() {

	while (1) {
		scanf("%lf%lf%lf%lf", &a, &b, &c, &d);
		if (fabs(a) < eps && fabs(b) < eps && fabs(c) < eps && fabs(d) < eps) break;
		scanf("%d", &N);
		for (int i = 0; i < N; ++i) pts[i].load();
		S.load();
		P = getPoint(a, b, c, d);
		V = point3(a, b, c);
		X = getVer(a, b, c).normalize();
		Y = det(X, V).normalize();
		solve();
	}

	return 0;

}
