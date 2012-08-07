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

const int MaxN = 7;

int N;
int R[MaxN], V[MaxN];

void resolve(int cnt, int i) {
	puts("DUP");
	int divisor = R[cnt] - R[i];
	printf("NUM %d\n", R[i]);
	puts("SUB");
	printf("NUM %d\n", divisor);
	puts("DIV");
	puts("SWP");
}

void solve(int cnt) {
	puts("DUP");
	printf("NUM %d\n", 1);
	puts("SWP");
	for (int i = 0; i < N; ++i) if (i != cnt) {
		resolve(cnt, i);
	}
	puts("POP");
	for (int i = 1; i < N; ++i) puts("MUL");
	puts("SWP");
}

int main() {

   	while (scanf("%d", &N) && N) {
		for (int i = 0; i < N; ++i) {
			scanf("%d%d", R + i, V + i);
		}
		for (int i = 0; i < N; ++i)
	    	solve(i);
		puts("POP");
		printf("NUM %d\n", 0);
		for (int i = 0; i < N; ++i) {
			puts("SWP");
			printf("NUM %d\n", V[N - 1 - i]);
			puts("MUL");
			puts("ADD");
		}
		puts("END");
		puts("");
	}

    return 0;

}

