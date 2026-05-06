int Gauss(Mat a, vector<int> &ans) {
  int n = a.n, m = a.m - 1;
  vector<int> pos(m, -1);
  int free_var = 0;
  const long long MODSQ = (long long)mod * mod;
  int rank = 0;
  for (int col = 0, row = 0; col < m && row < n; col++) {
    int mx = row;
    for (int k = row; k < n; k++) if (a.a[k][col] > a.a[mx][col]) mx = k;
    if (a.a[mx][col] == 0) continue;
    for (int j = col; j <= m; j++) swap(a.a[mx][j], a.a[row][j]);
    pos[col] = row;
    int inv = power(a.a[row][col], mod - 2);
    for (int i = 0; i < n && inv; i++) {
      if (i != row && a.a[i][col]) {
        int x = (1LL * a.a[i][col] * inv) % mod;
        for (int j = col; j <= m && x; j++) {
          if (a.a[row][j]) a.a[i][j] = (MODSQ + a.a[i][j] - 1LL * a.a[row][j] * x) % mod;
        }
      }
    }
    row++; ++rank;
  }
  ans.assign(m, 0);
  for (int i = 0; i < m; i++) {
    if (pos[i] == -1) free_var++;
    else ans[i] = (1LL * a.a[pos[i]][m] * power(a.a[pos[i]][i], mod - 2)) % mod;
  }
  for (int i = 0; i < n; i++) {
    long long val = 0;
    for (int j = 0; j < m; j++) val = (val + 1LL * ans[j] * a.a[i][j]) % mod;
    if (val != a.a[i][m]) return -1;
  }
  return free_var;
}