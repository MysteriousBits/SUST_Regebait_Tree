int n, k;
int li = 1, ri = 0, ansrng = 0; // current global answer
void update(int ind, bool type, bool inv) {/*...*/}
void shift(int ql, int qr) {
	while(li > ql) { --li; update(li, 0, 1); }
	while(ri < qr) { ++ri; update(ri, 0, 0); }
	while(li < ql) { update(li, 1, 0); li++; }
	while(ri > qr) { update(ri, 1, 1); ri--; }
}
 
void divconq(int K, int L, int R, int l, int r) {
	if(L > R) return;
	int M = (L+R) >> 1, best = l;
	for(int i = l; i <= min(M, r); i++) {
		shift(i, M);
		int cand = dp[K-1][i-1]+ansrng;
		if(cand <= dp[K][M]) { dp[K][M] = cand; best = i; }
	}
	divconq(K, L, M-1, l, best); divconq(K, M+1, R, best, r);
}
 