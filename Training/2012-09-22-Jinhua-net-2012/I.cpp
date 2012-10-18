#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<cctype>
#include<algorithm>
#include<vector>

using namespace std;

typedef pair<int, int> pii;
typedef long long LL;

const int MaxN = 100 + 5;

int N, M, P;
vector<pii> edges[11];
int fa[MaxN], tmp[MaxN], Map[MaxN], lab[MaxN], deg[MaxN], oldfa[MaxN], block[MaxN];
int mat[MaxN][MaxN];

int grand(int x) {
    if (fa[x] == x) return x;
    return fa[x] = grand(fa[x]);
}

void print(int tot) {
    for (int i = 0; i < tot; ++i) {
        for (int j = 0; j < tot; ++j) cout << mat[i][j] << ' ';
        puts("");
    }
}

int getMap() {
    int top = 0;    
    for (int i = 1; i <= N; ++i) 
        tmp[top++] = grand(i);
    sort(tmp, tmp + top);
    top = unique(tmp, tmp + top) - tmp;
    for (int i = 0; i < top; ++i)
        Map[tmp[i]] = i;    
    for (int i = 1; i <= N; ++i)
        lab[i] = Map[grand(i)];
    return top;
}

int getBlockMap(int blocklab) {
    int top = 0;    
    for (int i = 1; i <= N; ++i) if (block[i] == blocklab) 
        tmp[top++] = grand(i);
    sort(tmp, tmp + top);
    top = unique(tmp, tmp + top) - tmp;
    for (int i = 0; i < top; ++i)
        Map[tmp[i]] = i;    
    for (int i = 1; i <= N; ++i)
        lab[i] = Map[grand(i)];
    return top;
}

void construct(int now, int tot, int blocklab) {
    for (int i = 0; i < tot; ++i) deg[i] = 0;
    for (int i = 0; i < tot; ++i)
        for (int j = 0; j < tot; ++j) mat[i][j] = 0;
    for (int i = 0; i < (int)edges[now].size(); ++i) {
        int a = lab[edges[now][i].first], b = lab[edges[now][i].second];
        if (block[edges[now][i].first] != blocklab || block[edges[now][i].second] != blocklab) continue;
        if (a == b) continue;
        deg[a]++; deg[b]++;    
        mat[a][b]--; mat[b][a]--;
    }
    for (int i = 0; i < tot; ++i) 
        mat[i][i] = deg[i];
}

int getDet(int tot) {
    if (tot == 1) return 1;
    tot--;
    int sig = 1;
    for (int i = 0; i < tot; ++i) for (int j = 0; j < tot; ++j) mat[i][j] %= P;
    for (int i = 0; i < tot; ++i) {
        int k;    
        for (k = i; k < tot; ++k) if (mat[k][i]) break;
        if (k != i) {
            sig *= -1;
            for (int p = i; p < tot; ++p) swap(mat[i][p], mat[k][p]);
        }
        for (k = i + 1; k < tot; ++k) 
            while (mat[k][i]) {
                int t = mat[i][i] / mat[k][i];
                for (int p = i; p < tot; ++p)
                    mat[i][p] = (mat[i][p] - (LL)mat[k][p] * t) % P;
                    sig *= -1;
                    for (int p = i; p < tot; ++p) swap(mat[i][p], mat[k][p]);
            }
    }
    int res = sig;
    for (int i = 0; i < tot; ++i) res = (LL)res * mat[i][i] % P;
    return (res + P) % P;
}

void unionThem(int now) {
    for (int i = 0; i < (int)edges[now].size(); ++i) {
        int a = edges[now][i].first, b = edges[now][i].second;
        int fx = grand(a), fy = grand(b);
        if (fx != fy) fa[fy] = fx;
    }
}

int getBlock(int now) {
    for (int i = 1; i <= N; ++i) oldfa[i] = fa[i];    
    unionThem(now);
    int res = getMap();
    for (int i = 1; i <= N; ++i) block[i] = lab[i];
    for (int i = 1; i <= N; ++i) fa[i] = oldfa[i];    
    return res;
}

int main() {

    while (scanf("%d%d%d", &N, &M, &P) && (N || M || P)) {
        int u, v, w;
        for (int i = 1; i <= 10; ++i) edges[i].clear();
        while (M--) {
            scanf("%d%d%d", &u, &v, &w);    
            edges[w].push_back(pii(u, v));
        }
        if (P == 1) {
            puts("0");
            continue;
        }
        for (int i = 1; i <= N; ++i) fa[i] = i;    
        int Ans = 1;
        for (int i = 1; i <= 10; ++i) {
            int blocknum = getBlock(i);
            for (int k = 0; k < blocknum; ++k) {
                int tot = getBlockMap(k);
                construct(i, tot, k);
                Ans = (LL)Ans * getDet(tot) % P;
            }
            unionThem(i);
        }
        int gg = grand(1);
        for (int i = 2; i <= N; ++i) {
            if (grand(i) != gg) {
                printf("%d\n", 0);
                Ans = -1;
                break;
            }
        }
        if (Ans != -1) printf("%d\n", Ans);
    }

    return 0;

}
