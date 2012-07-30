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

const int MaxN = 100 + 5;
const LD pi = acos((LD)(-1.0));
const LD eps = 1e-12;

#define sq(x) ((x) * (x))

int N;

struct Point {
	LD x, y; int lab;
	Point() {}
	Point(LD _x, LD _y): x(_x), y(_y) {}
	void load() {
		cin >> x >> y;
		y = -y;
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
	LD dis(const Point &t) const {
		return sqrt(sq(x - t.x) + sq(y - t.y));
	}
	Point turn(LD d) {
		return Point(x * cos(d) - y * sin(d), x * sin(d) + y * cos(d));
	}
}pts[MaxN];

vector<LD> ang;
LD minlen, maxlen, minans, maxans;

void getAngs() {
	ang.clear();
	ang.push_back(0); ang.push_back(pi - eps);
	for (int i = 0; i < N; ++i)
		for (int j = i + 1; j < N; ++j) {
			Point tmp = pts[j] - pts[i];
			ang.push_back(atan2(tmp.y, tmp.x));
			LD d = asin(2 / pts[i].dis(pts[j]));
			ang.push_back(atan2(tmp.turn(d).y, tmp.turn(d).x));	
			ang.push_back(atan2(tmp.turn(-d).y, tmp.turn(-d).x));
		}
	for (int i = 0; i < (int)ang.size(); ++i)
		if (ang[i] < 0) ang[i] += pi;
	sort(ang.begin(), ang.end());
		
}

vector<LD> tmp;

void check(LD d) {
	tmp.clear();
	for (int i = 0; i < N; ++i)
		tmp.push_back(pts[i].turn(-d).y);
	LD len = 2;
	sort(tmp.begin(), tmp.end());
	for (int i = 0; i + 1 < (int)tmp.size(); ++i) {
		if (tmp[i + 1] - tmp[i] < 2) len += tmp[i + 1] - tmp[i];
		else len += 2;
	}
	if (len < minlen) {
		minlen = len;
		minans = d;
	}
	if (len > maxlen) {
		maxlen = len;
		maxans = d;
	}
}

typedef pair<LD, int> pii;
vector<pii> P;

LD makeAng(LD d) {
	P.clear();
	for (int i = 0; i < N; ++i)
		P.push_back(pii(pts[i].turn(-d).y, i));
	sort(P.begin(), P.end());
	LD dx = 0, dy = 0;
	for (int i = 0; i < (int)P.size(); ++i) {
		int j = i;
		while (j + 1 < (int)P.size() && P[j + 1].first - P[j].first < 2) j++;
		int p1 = P[i].second, p2 = P[j].second;	
		dx += pts[p2].x - pts[p1].x; dy += pts[p2].y - pts[p1].y;
		i = j;
	}
	LD res = atan2(dx, -dy);
	if (res < 0) res += pi;
	return res;
}

int main() {

	cout.precision(12); cout << fixed;
	while (scanf("%d", &N) && N) {
		for (int i = 0; i < N; ++i) pts[i].load();	
		getAngs();	
		minlen = 1e20; maxlen = 0;
		for (int i = 0; i + 1 < (int)ang.size(); ++i) {
			check(ang[i]); check(ang[i + 1]);
			check(makeAng((ang[i] + ang[i + 1]) / 2));
		}
		cout << minans << endl << maxans << endl;
	}

    return 0;

}

