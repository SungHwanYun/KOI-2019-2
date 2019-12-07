#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib> 
#include <ctime>
#include <unordered_map>
using namespace std;
typedef long long ll;
/*
input
6 0
5 1 5 4 0 1
1 4 2 3 5 5
0 4 0 5 5 1
4 5 4 5 1 4
4 2 4 1 4 4
2 5 3 0 2 2

output
-1

input
6 1
5 1 5 4 0 1
1 4 2 3 5 5
0 4 0 5 5 1
4 5 4 5 1 4
4 2 4 1 4 4
2 5 3 0 2 2

output
19
*/
struct info {
	int r, c, d;
	struct info(int a1, int a2, int a3) {
		r = a1; c = a2; d = a3;
	}
	struct info() {}
};
int N, K, A[52][52], B[52][52], X[6][2] = { {0,1},{1,2},{0,3},{2,3},{1,3},{0,2} };
int g(int ur, int uc, int ud, int &vr, int &vc, int &vd) {
	vr = ur; vc = uc;
	if (ud == 0) {
		vc++;
		if (vc == N) return 0;
		if (A[vr][vc] == 1) vd = 1;
		else if (A[vr][vc] == 3) vd = 0;
		else if (A[vr][vc] == 5) vd = 1;
		else return 0;
	}
	else if (ud == 1) {
		vr++;
		if (vr == N) return 0;
		if (A[vr][vc] == 2 || A[vr][vc] == 3 || A[vr][vc] == 4) vd = 1;
		else return 0;
	}
	else if (ud == 2) {
		vc--;
		if (vc < 0) return 0;
		if (A[vr][vc] == 0 || A[vr][vc] == 2 || A[vr][vc] == 5) vd = 0;
		else return 0;
	}
	else {
		vr--;
		if (vr < 0) return 0;
		if (A[vr][vc] == 0) vd = 1;
		else if (A[vr][vc] == 1) vd = 0;
		else if (A[vr][vc] == 4) vd = 0;
		else return 0;
	}
	return 1;
}
int f() {
	if (A[0][0] == 0 || A[0][0] == 2 || A[0][0] == 4) return -1;
	if (A[N - 1][N - 1] == 1 || A[N - 1][N - 1] == 3 || A[N - 1][N - 1] == 4) return -1;
	int i, j;
	for (i = 0; i < N; i++) for (j = 0; j < N; j++) B[i][j] = -1;
	queue <struct info> Q;
	if (A[0][0]==1) Q.push(struct info(0,0,1));
	else if (A[0][0]==3) Q.push(struct info(0, 0, 0));
	else if (A[0][0] == 5) Q.push(struct info(0, 0, 1));
	B[0][0] = 1;
	while (!Q.empty()) {
		int ur, uc, ud, vr, vc, vd, a, b; struct info u, v;
		u = Q.front();
		ur = u.r; uc = u.c; ud = u.d;
		Q.pop();
		if (ur == N - 1 && uc == N - 1) {
			return B[ur][uc];
		}
		a = X[A[ur][uc]][ud]; b = X[A[ur][uc]][1 - ud]; // a->b ¹æÇâ
		if (g(ur, uc, b, vr, vc, vd) == 0) continue;
		if (B[vr][vc] != -1) continue; // cycle
		Q.push(struct info(vr, vc, vd));
		B[vr][vc] = B[ur][uc] + 1;
	}
	return -1;
}
int main() {
	int i, j, k, ans=INT_MAX;
	scanf("%d%d\n", &N, &K);
	for (i = 0; i < N; i++) for (j = 0; j < N; j++) scanf("%d", &A[i][j]);
	if (K == 0) {
		printf("%d\n", f());
	}
	else {
		for (i = 0; i < N; i++) for (j = 0; j < N; j++) for (k = 0; k < 6; k++) {
			if (A[i][j] == k) continue;
			int a = A[i][j], b;
			A[i][j] = k;
			b = f();
			if (b != -1) ans = min(ans, b);
			A[i][j] = a;
		}
		if (ans == INT_MAX) ans = -1;
		printf("%d\n", ans);
	}
	return 0;
}
