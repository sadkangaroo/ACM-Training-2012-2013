#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<cctype>
#include<algorithm>

using namespace std;

const int MaxN = 100000 + 5;

int N;
int c[MaxN];
int mi[MaxN * 4], delta[MaxN * 4];

void add(int now, int x) {
    delta[now] += x; mi[now] += x;
}

void modify(int now, int l, int r, int a, int b, int x) {
    if (a > b) return;
    if (a <= l && b >= r) {
        add(now, x);
        return;
    }
    add(now * 2, delta[now]);
    add(now * 2 + 1, delta[now]);
    delta[now] = 0;
    int mid = ((l + r) >> 1);
    if (a <= mid) modify(now * 2, l, mid, a, b, x);
    if (b > mid) modify(now * 2 + 1, mid + 1, r, a, b, x);
    mi[now] = min(mi[now * 2], mi[now * 2 + 1]);
}

int val;

int getMin(int now, int l, int r) {
    if (l == r) {
        val = mi[now];
        return l;
    }
    add(now * 2, delta[now]);
    add(now * 2 + 1, delta[now]);
    delta[now] = 0;
    int mid = ((l + r) >> 1);
    if (mi[now * 2] <= mi[now * 2 + 1])
        return getMin(now * 2, l, mid);
    else return getMin(now * 2 + 1, mid + 1, r);
}

const int oo = 100000000;

int ans[2 * MaxN];
int tmp[MaxN], top;

bool solve() {
    int p = 0;
    top = 0;
    for (int i = 2 * N; i >= 1; --i) {
        if (p == top) {
            int pos = getMin(1, 1, N);
            if (val == 0) {
                ans[i] = pos;
                tmp[top++] = pos;
                modify(1, 1, N, 1, pos - 1, -1);
                modify(1, 1, N, pos, pos, oo);
                continue;
            }
            else return false;
        }
        int pos = getMin(1, 1, N);
        if (val == 0) {
            ans[i] = pos;
            tmp[top++] = pos;
            modify(1, 1, N, 1, pos - 1, -1);
            modify(1, 1, N, pos, pos, oo);
            continue;
        }
        if (p < top) {
            ans[i] = -tmp[p];
            modify(1, 1, N, tmp[p] + 1, N, -1);
            p++;
        }
        else return false;
    }
    return true;
}

int main() {

    while (scanf("%d", &N) && N) {
        for (int i = 1; i <= N; ++i)
            scanf("%d", c + i);
        memset(mi, 0, sizeof(mi));
        memset(delta, 0, sizeof(delta));  
        for (int i = 1; i <= N; ++i)
            modify(1, 1, N, i, i, c[i]);
        if (solve()) {
            for (int i = 1; i <= 2 * N; ++i)
                printf("%d ", ans[i]);
            printf("\n");
        }
        else puts("Impossible");
    }
    
    return 0;

}
