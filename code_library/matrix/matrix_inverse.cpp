bool Inv(Mat a, Mat &ans) {
  assert(a.n == a.m);
  int n = a.n;
  vector<int> col(n);
  Mat tmp(n, n); tmp.make_unit();
  for (int i = 0; i < n; i++) col[i] = i;
  for (int i = 0; i < n; i++) {
    int r = i, c = i;
    for (int j = i; j < n; j++)
      for (int k = i; k < n; k++)
        if (a.a[j][k]) { r = j; c = k; goto found; }
    return false;
    found:
    a.a[i].swap(a.a[r]); tmp.a[i].swap(tmp.a[r]);
    for (int j = 0; j < n; j++) { swap(a.a[j][i], a.a[j][c]); swap(tmp.a[j][i], tmp.a[j][c]); }
    swap(col[i], col[c]);
    int v = power(a.a[i][i], mod - 2);
    for (int j = i + 1; j < n; j++) {
      int f = 1LL * a.a[j][i] * v % mod;
      a.a[j][i] = 0;
      for (int k = i + 1; k < n; k++) {
        a.a[j][k] -= 1LL * f * a.a[i][k] % mod;
        if (a.a[j][k] < 0) a.a[j][k] += mod;
      }
      for (int k = 0; k < n; k++) {
        tmp.a[j][k] -= 1LL * f * tmp.a[i][k] % mod;
        if (tmp.a[j][k] < 0) tmp.a[j][k] += mod;
      }
    }
    for (int j = i + 1; j < n; j++) a.a[i][j] = 1LL * a.a[i][j] * v % mod;
    for (int j = 0; j < n; j++) tmp.a[i][j] = 1LL * tmp.a[i][j] * v % mod;
    a.a[i][i] = 1;
  }
  for (int i = n - 1; i > 0; --i) {
    for (int j = 0; j < i; j++) {
      int v = a.a[j][i];
      for (int k = 0; k < n; k++) {
        tmp.a[j][k] -= 1LL * v * tmp.a[i][k] % mod;
        if (tmp.a[j][k] < 0) tmp.a[j][k] += mod;
      }
    }
  }
  ans = Mat(n, n);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      ans.a[col[i]][col[j]] = tmp.a[i][j];
  return true;
}