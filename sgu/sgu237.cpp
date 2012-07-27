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

const int MaxLen = 255 * 3 + 20;

char ss[MaxLen], s[MaxLen];
int len, p0, p1, p2;
bool f[3][MaxLen];
string g[3][MaxLen];

#define current f[p2][l], g[p2][l]

void update(bool &a, string &b, string c) {
	if (!a) {
		a = true;
		b = c; return;
	}
	if (c.length() < b.length() || c.length() == b.length() && c < b) b = c;
}

void solve() {
	p0 = 0, p1 = 1, p2 = 2;
	for (int k = 2; k <= len; ++k) {
		for (int l = 0; l + k - 1 < len; ++l) {
			int r = l + k - 1;
			char cl = s[l], cr = s[r];
			f[p2][l] = false;
			if (cl == '*') {
				if (cr == '*') {
					if (f[p1][l + 1]) update(current, g[p1][l + 1]);	
					if (f[p1][l]) update(current, g[p1][l]);
				}
				else if (cr == '?') {
					if (f[p1][l + 1]) update(current, g[p1][l + 1]);	
					if (f[p1][l]) update(current, 'a' + g[p1][l] + 'a');
				}
				else {
					if (f[p1][l + 1]) update(current, g[p1][l + 1]);	
					if (f[p1][l]) update(current, cr + g[p1][l] + cr);
				}
			}
			else if (cl == '?') {
				if (cr == '*') {
					if (f[p1][l]) update(current, g[p1][l]);
					if (f[p1][l + 1]) update(current, 'a' + g[p1][l + 1] + 'a');
				}
				else if (cr == '?') {
					if (f[p0][l + 1]) update(current, 'a' + g[p0][l + 1] + 'a');
				}
				else {
					if (f[p0][l + 1]) update(current, cr + g[p0][l + 1] + cr);
				}
			}
			else {
				if (cr == '*') {
					if (f[p1][l]) update(current, g[p1][l]);
					if (f[p1][l + 1]) update(current, cl + g[p1][l + 1] + cl);
				}
				else if (cr == '?') {
					if (f[p0][l + 1]) update(current, cl + g[p0][l + 1] + cl);
				}
				else {
					if (f[p0][l + 1] && cl == cr) update(current, cl + g[p0][l + 1] + cl);
				}
			}
		}
		p0 = p1; p1 = p2; p2 = 3 - p1 - p0;
	}
}

int main() {

   	gets(ss); int ll = strlen(ss); 
	len = 0;
	for (int i = 0; i < ll; ++i) {
		if (ss[i] == '!') {
			for (int k = 0; k < 3; ++k) s[len++] = '?'; 
		}
		else s[len++] = ss[i];	
	} s[len] = 0;
	memset(f, true, sizeof(f));
	for (int i = 0; i < len; ++i) g[0][i] = "";
	for (int i = 0; i < len; ++i) {
		if (s[i] == '*') g[1][i] = "";
		else if (s[i] == '?') g[1][i] = "a";
			 else g[1][i] = s[i];
	}
	solve();
	if (f[p1][0]) {
		cout << "YES" << endl;
		cout << g[p1][0] << endl;
	}
	else cout << "NO" << endl;

    return 0;

}

