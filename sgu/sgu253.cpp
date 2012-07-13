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

const int MaxN = 100000 + 5;

int N, M, K;

struct Point {
    LL x, y;
    Point() {}
    Point(LL _x, LL _y): x(_x), y(_y) {}
    void load() {
        int _x, _y;
        scanf("%d%d", &_x, &_y);
        x = (LL)_x; y = (LL)_y;
    }
    Point operator - (const Point &t) const {
        return Point(x - t.x, y - t.y);
    }
    LL det(const Point &t) const {
        return x * t.y - y * t.x;
    }
    void print() {
        cout << x << ' ' << y << endl;
    }
};

Point pts[MaxN];

inline LL area2(const Point &a, const Point &b, const Point &c) {
    return (b - a).det(c - a);
}

bool check(Point p, Point* pts, int N) {
    int L = 1,  R = N - 2, Mid;
    while (L < R) {
        Mid = (L + R + 1) >> 1;
        if (area2(pts[0], pts[Mid], p) >= 0) L = Mid;
        else R = Mid - 1;
    }
    Mid = L;
    return area2(pts[0], pts[Mid], p) >= 0 && area2(pts[Mid], pts[Mid + 1], p) >= 0 
        && area2(pts[Mid + 1], pts[0], p) >= 0;
}

int main() {

    scanf("%d%d%d", &N, &M, &K); 
    for (int i = 0; i < N; ++i) 
        pts[i].load();
    Point now;
    int tot = 0;
    for (int i = 0; i < M; ++i) {
        now.load();
        if (check(now, pts, N)) tot++;
    }
    if (tot >= K) puts("YES");
    else puts("NO");

    return 0;

}
