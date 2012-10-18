#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;

const int MaxM = 100 + 5;
const int MaxN = 100 + 5;

int T, N, M, Y, X, D, tot;
int P[MaxM], lab[MaxN][2];
bool ok[MaxN][2];
double mat[MaxN * 2][MaxN * 2];

int go(int now, int dir, int step, int& newdir) {
    if (dir == 0) {
        if (step < N - 1 - now) {
            newdir = dir; return now + step;
        }
        else {
            step -= (N - 1 - now);
            step %= (2 * N - 2);
            if (step < N - 1) {
                newdir = 1;
                return N - 1 - step;
            }
            else {
                newdir = 0;
                return step - (N - 1);
            }
        }
    }
    else {
        if (step < now) {
            newdir = dir; return now - step;
        }
        else {
            step -= now;
            step %= (2 * N - 2);
            if (step < N - 1) {
                newdir = 0;
                return step;
            }
            else {
                newdir = 1;
                return N - 1 - (step - (N - 1));
            }
        }
    }
}

void dfs(int now, int d) {
    int dd;
    if (now == 0) dd = 0;
    else if (now == N - 1) dd = 1; 
    else dd = (d ^ 1);
    if (ok[now][dd]) return;
    ok[now][dd] = true;
    for (int k = 1; k <= M; ++k)
        if (P[k]) {
            int newd;
            int nxt = go(now, d, k, newd);
            dfs(nxt, newd);
        }
}

void relabel() {
    tot = 0; int other1, other2;    
    for (int i = 0; i < N; ++i) { 
        for (int dir = 0; dir <= 1; ++dir) if (ok[i][dir]) {
            lab[i][dir] = tot++;
            other1 = i;
            other2 = dir;
        }
    }
    swap(lab[X][D], lab[other1][other2]);
}

const double eps = 1e-8;

void solve() {
    for (int i = 0; i < tot; ++i)
        for (int j = 0; j <= tot; ++j) mat[i][j] = 0;
    if (Y != N - 1) {
        int tmp = lab[Y][0];
        mat[tmp][tmp] = 1;
    }
    if (Y != 0) {
        int tmp = lab[Y][1];
        mat[tmp][tmp] = 1;
    }
    for (int i = 0; i < N; ++i) if (i != Y) {
        for (int dir = 0; dir <= 1; ++dir) if (ok[i][dir]) {
            int now = lab[i][dir];
            mat[now][now] = 1;
            for (int k = 1; k <= M; ++k) if (P[k]) {
                int newd;
                int tmp = go(i, dir, k, newd);
                int nxt = lab[tmp][newd];    
                mat[now][nxt] -= (P[k] / 100.0);
                mat[now][tot] += (P[k] / 100.0 * k);
            }
        }
    }
    for (int i = 0; i < tot; ++i) {
        int k;
        for (k = i; k < tot; ++k) if (fabs(mat[k][i]) > eps) break;
        for (int p = i; p <= tot; ++p) swap(mat[i][p], mat[k][p]);
        for (k = i + 1; k < tot; ++k) if (fabs(mat[k][i]) > eps) {
            double t = mat[k][i] / mat[i][i];        
            for (int p = i; p <= tot; ++p) {
                mat[k][p] -= t * mat[i][p];
            }
        }
    }
    printf("%.2f\n", fabs(mat[tot - 1][tot] / mat[tot - 1][tot - 1]));
}
    
int main() {

    scanf("%d", &T);    
    while (T--) {
        scanf("%d%d%d%d%d", &N, &M, &Y, &X, &D);    
        if (X == 0) D = 0;
        if (X == N - 1) D = 1;
        for (int k = 1; k <= M; ++k) {
            scanf("%d", P + k);    
        }
        if (N == 1) {
            puts("0.00");
            continue;
        }
        memset(ok, false, sizeof(ok));
        if (Y != N - 1) dfs(Y, 0); 
        if (Y != 0) dfs(Y, 1);
        if (!ok[X][D]) {
            puts("Impossible !");
            continue;
        }
        relabel();
        solve();
    }

    return 0;

}
