array<vector<int>, 2> manacher(const string& s) {
	int n = s.size();
	array<vector<int>,2> p = {vector<int>(n+1), vector<int>(n)};
	for (int z=0; z<2; z++) for (int i=0,l=0,r=0; i < n; i++) {
		int t = r-i+!z;
		if (i<r) p[z][i] = min(t, p[z][l+t]);
		int L = i-p[z][i], R = i+p[z][i]-!z;
		while (L>=1 && R+1<n && s[L-1] == s[R+1])
			p[z][i]++, L--, R++;
		if (R>r) l=L, r=R;
	}
	return p;
}
bool is_palindrome(int l, int r, const array<vector<int>, 2>& p) {
  int len = r - l + 1;
  if (len <= 0) return true;
  if (len % 2 == 1) {
    int mid = (l + r) / 2;
    return p[1][mid] >= len / 2;
  } else {
    int mid = (l + r + 1) / 2;
    return p[0][mid] >= len / 2;
  }
}