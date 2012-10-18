#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<cctype>
#include<algorithm>
#include<vector>

using namespace std;

const double eps = 1e-8;
const double INF = 1e15;
const double BOUND = 1e12;

struct Key {
	double x, y; bool taken;
	Key(double _x, double _y): x(_x), y(_y), taken(false) {}
	Key(double _x, double _y, bool _taken): 
		x(_x), y(_y) {taken = _taken;}
	bool operator < (const Key &t) const {
		return x < t.x;
	}
};

double normalize(double x) {
    if (fabs(x) < eps) return 0;
    else return x;
}

struct Interval {
	double l; int tl; double r; int tr;		
	Interval(double _l, int _tl, double _r, int _tr):
		l(_l), tl(_tl), r(_r), tr(_tr) {}
	bool operator < (const Interval &t) const {
		if (fabs(l - t.l) < eps) return tl > t.tl;
		else return l < t.l;
	}
	void print() {
		if (tl == 0) putchar('(');
		else putchar('[');
		if (l < -BOUND) printf("-INF");
		else if (l > BOUND) printf("INF");
		else printf("%.4f", normalize(l));
		printf(", ");
		if (r < -BOUND) printf("-INF");
		else if (r > BOUND) printf("INF");
		else printf("%.4f", normalize(r));
		if (tr == 0) putchar(')');
		else putchar(']');
	}
};

vector<Key> keypoints;
vector<Interval> intervals, ans;

int T;
double A, B, C, D, E, P, Q;

double f(double x) {
	return (A * x * x + B * x + C) / (x * x + D * x + E);
}

double Lhospital(double x0) {
	if (fabs(P * x0 + Q) > eps) {
		return INF;
	}
	else {
		if (fabs(2 * x0 + D) > eps) return A + P / (2 * x0 + D);
		else if (fabs(P) < eps) {
			return A;
		}
		else return INF;
	}
}

void addZero() {
	double delta = D * D - 4 * E, x0;
	if (fabs(delta) < eps) {
		x0 = -D / 2;	
		keypoints.push_back(Key(x0, Lhospital(x0), true));
	}
	else if (delta > 0) {
		x0 = (-D - sqrt(delta)) / 2.0;
		keypoints.push_back(Key(x0, Lhospital(x0), true));
		x0 = (-D + sqrt(delta)) / 2.0;
		keypoints.push_back(Key(x0, Lhospital(x0), true));
	}
}

bool zero(double x) {
	return fabs(x * x + D * x + E) < eps;	
}

void addPeak() {
	double x0;
	if (fabs(P) < eps) {
		x0 = (P * E - Q * D) / (2 * Q);
		if (!zero(x0)) keypoints.push_back(Key(x0, f(x0)));
		
	}
	else {
		double delta = Q * Q + P * (P * E - Q * D);
		if (fabs(delta) < eps) {
			x0 = -Q / P;
			if (!zero(x0)) keypoints.push_back(Key(x0, f(x0)));
		}
		else if (delta > 0) {
			x0 = (Q - sqrt(delta)) / (-P);
			if (!zero(x0)) keypoints.push_back(Key(x0, f(x0)));
			x0 = (Q + sqrt(delta)) / (-P);
			if (!zero(x0)) keypoints.push_back(Key(x0, f(x0)));
		}
	}
}

void output() {
	bool isFirst = true;
	for (int i = 0; i < (int)ans.size(); ++i) {
		if (isFirst) isFirst = false;
		else {
			printf(" U ");
		}
		ans[i].print();
	}
	puts("");
}

void solve() {
	addZero();
	keypoints.push_back(Key(-INF, A, true)); keypoints.push_back(Key(INF, A, true));
	addPeak();
	sort(keypoints.begin(), keypoints.end());
	for (int i = 0; i + 1 < (int)keypoints.size(); ++i) {
		Key a = keypoints[i], b = keypoints[i + 1];
		double x1 = a.x + min(1.0, (b.x - a.x) / 3.0), x2 = b.x - min(1.0, (b.x - a.x) / 3.0);
		if (f(x1) > f(x2)) swap(a, b);
		double da, db; int ta, tb;
		if (a.y > BOUND) da = -INF;
		else da = a.y;
		if (b.y > BOUND) db = INF; 
		else db = b.y;
		intervals.push_back(Interval(da, !a.taken, db, !b.taken));
	}
	sort(intervals.begin(), intervals.end());
	double nl = intervals[0].l, nr = intervals[0].r; 
	int tl = intervals[0].tl, tr = intervals[0].tr;
	for (int i = 1; i < (int)intervals.size(); ++i) {
		Interval now = intervals[i];	
		if (now.l < nr - eps || (fabs(now.l - nr) < eps && tr + now.tl >= 1)) {
			if (now.r > nr + eps || (fabs(now.r - nr) < eps && now.tr >= tr)) {
				nr = now.r; tr = now.tr;
			}
		}
		else {
			ans.push_back(Interval(nl, tl, nr, tr));
			nl = now.l, nr = now.r; 
			tl = now.tl, tr = now.tr;
		}
	}
	ans.push_back(Interval(nl, tl, nr, tr));
	output();
}

int main() {

	scanf("%d", &T);	
	while (T--) {
		keypoints.clear();
		intervals.clear();
		ans.clear();
		scanf("%lf%lf%lf%lf%lf", &A, &B, &C, &D, &E);	
		P = B - A * D; Q = C - A * E;
		if (fabs(P) < eps && fabs(Q) < eps) {
			Interval(A, 1, A, 1).print();	
			puts("");
		}
		else solve();
	}

	return 0;

}
