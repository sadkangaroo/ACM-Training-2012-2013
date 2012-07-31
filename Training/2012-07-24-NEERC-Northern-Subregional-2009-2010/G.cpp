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

typedef long double LD;

const LD pi = acos((LD)(-1.0));
const int MaxN = 10 + 5, MaxM = 100 + 5;
const LD eps = 1e-10;

#define sq(x) ((x) * (x))

LD normalize(LD x) {
	while (x < 0) x += 2 * pi;
	while (x >= 2 * pi) x -= 2 * pi;
	return x;
}

struct Point {
	LD x, y, r, a;	
	void load() {
		cin >> r >> a;
		a = a / 180.0 * pi;
		a = normalize(a);
		x = r * cos(a);
		y = r * sin(a);
	}
	Point() {}
	Point(LD _x, LD _y): x(_x), y(_y) {
		r = sqrt(sq(x) + sq(y));	
		a = atan2(y, x);
		a = normalize(a);
	}
	Point operator + (const Point &t) const {
		return Point(x + t.x, y + t.y);
	}
	Point operator - (const Point &t) const {
		return Point(x - t.x, y - t.y);
	}
	Point operator * (LD t) const {
		return Point(x * t, y * t);
	}
	Point operator / (LD t) const {
		return Point(x / t, y / t);
	}
	LD dot(const Point &t) const {
		return x * t.x + y * t.y;
	}
	LD mo() {
		return sqrt(sq(x) + sq(y));
	}
	Point turn() const {
		return Point(-y, x);
	}
	Point unit() {
		return *this / mo();
	}
	LD det(const Point &t) const {
		return x * t.y - y * t.x;
	}
	LD angleTo(const Point &t) {
		return normalize(t.a - a);
	}
};

struct Polygon {
	int n;	
	Point v[MaxM];
	LD area() {
		LD res = 0;
		for (int i = 0; i < n; ++i) res += v[i].det(v[i + 1]);
		return res / 2;
	}
	void load() {
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) v[i].load();
		v[n] = v[0];
		if (area() < 0) {
			for (int i = 0; i < n - 1 - i; ++i) swap(v[i], v[n - 1 - i]);
		}
		v[n] = v[0];
	}
}bolt, wrench[MaxN];

struct Interval {
	LD l, r;
	Interval(LD _l, LD _r) {
		l = normalize(_l); r = normalize(_r);
		if (r < l) r += 2 * pi;
	}
	bool operator < (const Interval &t) const {
		if (fabs(l - t.l) < eps) return r < t.r;
		return l < t.l;
	}
	vector<Interval> intersectWith(Interval t) const {
		vector<Interval> res;
		if (l > r || t.l > t.r) return res;
		if (t.l > l) {
			t.l -= 2 * pi;
			t.r -= 2 * pi;
		}
		LD ll = max(l, t.l), rr = min(r, t.r);
		if (ll + eps < rr) res.push_back(Interval(ll, rr));
		t.l += 2 * pi; t.r += 2 * pi;
		ll = max(l, t.l), rr = min(r, t.r);
		if (ll + eps < rr) res.push_back(Interval(ll, rr));
		return res;
	}
};

vector<Interval> forbidden; 
vector<LD> delta;

void addAll(vector<Interval> &a, vector<Interval> &b) {
	for (int i = 0; i < b.size(); ++i)
		a.push_back(b[i]);
}

vector<LD> getDelta(Point a, Point b, Point c) {
	vector<LD> res; res.clear();
	Point ver = (b - c).turn().unit();
	LD t = c.dot(ver);
	LD _cos = t / a.r;
	if (_cos > 1 + eps) return res;
	if (_cos > 1) _cos = 1;
	LD d = acos(_cos), alpha;
	alpha = a.angleTo((ver * t));
	res.push_back(normalize(alpha - d));
	res.push_back(normalize(alpha + d));
	return res;
}

bool canOpen(Polygon wrench, Polygon bolt) {
	if (wrench.area() > bolt.area() + eps) return false;	
	forbidden.clear();
	for (int j = 0; j < bolt.n; ++j) 
		for (int i = 0; i < wrench.n; ++i) {
			delta = getDelta(wrench.v[i], bolt.v[j], bolt.v[j + 1]);	
			if (delta.size()) {
				vector<Interval> s = Interval(delta[0] + eps, delta[1] - eps)
					.intersectWith(Interval(wrench.v[i].angleTo(bolt.v[j]) - eps, wrench.v[i].angleTo(bolt.v[j + 1]) + eps));
				addAll(forbidden, s);
			}
			delta = getDelta(bolt.v[j], wrench.v[i], wrench.v[i + 1]);	
			if (delta.size()) {
				vector<Interval> s = Interval(-delta[0] + eps, -delta[1] - eps)
					.intersectWith(Interval(wrench.v[i + 1].angleTo(bolt.v[j]) - eps, wrench.v[i].angleTo(bolt.v[j]) + eps));
				addAll(forbidden, s);
			}
			else forbidden.push_back(Interval(wrench.v[i + 1].angleTo(bolt.v[j]) - eps, wrench.v[i].angleTo(bolt.v[j]) + eps));
		}
	if (forbidden.size() == 0) return false;
	sort(forbidden.begin(), forbidden.end());
	LD last = 0;
	for (int i = 0; i < forbidden.size(); ++i) {
		last = max(last, forbidden[i].r - 2 * pi);	
	}
	if (last == 0) return true;
	for (int i = 0; i < forbidden.size(); ++i) {
		if (forbidden[i].l > last) return true;
		last = max(last, forbidden[i].r);
	}
	return false;
}

int N; LD R;
vector<int> ans;

int main() {

	cout.precision(12);
	cout << fixed;
	cin >> N >> R;
	bolt.load();
	for (int i = 0; i < N; ++i) wrench[i].load();
	for (int i = 0; i < N; ++i) if (canOpen(wrench[i], bolt)) ans.push_back(i);
	cout << ans.size() << endl;
	for (int i = 0; i < ans.size(); ++i) {
		if (i + 1 == ans.size()) cout << ans[i] + 1 << endl;
		else cout << ans[i] + 1 << ' ';
	}

    return 0;

}

