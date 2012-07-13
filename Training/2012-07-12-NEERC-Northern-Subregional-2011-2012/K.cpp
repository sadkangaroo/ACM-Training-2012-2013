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

const int MaxN = 5000 + 5;

struct Point {
    LL x, y; int lab;
    Point() {}
    Point(LL _x, LL _y): x(_x), y(_y) {}
    void load(int _lab) {
        cin >> x >> y;
        lab = _lab;
    }
    bool operator < (const Point & t) const {
        if (y != t.y) return y < t.y;
        return x < t.x;
    }
    Point operator - (const Point &t) const {
        return Point(x - t.x, y - t.y);
    }
    LL det(const Point &t) {
        return x * t.y - y * t.x;
    }
};

LL area2(const Point &a, const Point &b, const Point &c) {
    return (b - a).det(c - a);
}

int graham(Point* pts, int N, Point* stk) {
    int top = 0;
    for (int i = 0; i < N; ++i) {
        while (top >= 2 && area2(stk[top - 2], stk[top - 1], pts[i]) <= 0) top--;
        stk[top++] = pts[i];
    }
    int base = top - 1;
    for (int i = N - 1; i >= 0; --i) {
        while (top - base >= 2 && area2(stk[top - 2], stk[top - 1], pts[i]) <= 0) top--;
        stk[top++] = pts[i];
    }
    return top - 1;
}

int a1, a2, a3, b1, b2, b3, typ, p0;
bool flag;

bool update(LL &ans, LL newans, int _p0, int _typ) {
    if (newans > ans) {
        ans = newans; flag = true; p0 = _p0; typ = _typ;
        return true;
    } return false;
}

void calc(int st, LL &ans, Point* pts, int N) {
    int p = st + 3, q;
    for (int i = st + 2; i < st + N - 1; ++i) {
        while (area2(pts[st], pts[i], pts[p + 1]) > area2(pts[st], pts[i], pts[p])) p++;
        LL S = area2(pts[st], pts[i], pts[p]);
        flag = false;
        update(ans, S - area2(pts[st], pts[st + 1], pts[i]), st + 1, 0);
        update(ans, S - area2(pts[st], pts[i - 1], pts[i]), i - 1, 0);
        if (i == st + 2 || area2(pts[i - 2], pts[i - 1], pts[i]) < area2(pts[q - 2], pts[q - 1], pts[q])) q = i;
        update(ans, S - area2(pts[q - 2], pts[q - 1], pts[q]), q, 1);
        if (flag) {a1 = pts[st].lab; a2 =pts[i].lab; a3 = pts[p].lab;}
    }
}

Point pts[MaxN * 2], stk[MaxN];
int N;
LL ans;

int main() {

    cin >> N; 
    for (int i = 0; i < N; ++i) pts[i].load(i + 1);
    N = graham(pts, N, stk);
    for (int i = 0; i < N; ++i) pts[i] = stk[i];
    for (int i = N; i < 2 * N; ++i) pts[i] = pts[i - N];
    ans = -1;
    for (int i = 0; i < N; ++i) calc(i, ans, pts, N);
    if (typ == 0) {b1 = a1; b2 = a2; b3 = pts[p0].lab;}
    else {b1 = pts[p0 - 2].lab; b2 = pts[p0 - 1].lab; b3 = pts[p0].lab;}
    if (ans & 1) cout << ans / 2 << ".5" << endl;
    else cout << ans / 2 << ".0" << endl;
    cout << a1 << ' ' << a2 << ' ' << a3 << endl;
    cout << b1 << ' ' << b2 << ' ' << b3 << endl;

    return 0;

}
