void lp(string& s) {
  string t = s;
  reverse(t.begin(), t.end());
  int n = s.size();
  Hash sh(s), th(t);
  auto f = [&](int L, int R) {
    auto ss = sh.geth(L, R);
    auto tt = th.geth(n - R + 1, n - L + 1);
    return (ss == tt);
  };
  vector<int> R(n, 1), L(n, 1);
  for (int i = n - 1, r = n - 1; i >= 0; i--) {
    if (r < n - 1 && s[i] == s[r + 1]) {
      r++;
    } else {
      while (!f(i + 1, r + 1)) {
        r--;
      }
    }
    R[i] = max(R[i], r - i + 1);
  }
  for (int i = 0, l = 0; i < n; i++) {
    if (l > 0 && s[i] == s[l - 1]) {
      l--;
    } else {
      while (!f(l + 1, i + 1)) {
        l++;
      }
    }
    L[i] = max(L[i], i - l + 1);
  }
}