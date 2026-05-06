int Det(Mat a) {
  assert(a.n == a.m);
  int n = a.n;
  const long long MODSQ = (long long)mod * mod;
  int det = 1;
  for (int col = 0, row = 0; col < n && row < n; col++) {
    int mx = row;
    for (int k = row; k < n; k++) if (a.a[k][col] > a.a[mx][col]) mx = k;
    if (a.a[mx][col] == 0) { det = 0; continue; }
    for (int j = col; j < n; j++) swap(a.a[mx][j], a.a[row][j]);
    if (row != mx) det = (det == 0 ? 0 : mod - det);
    det = 1LL * det * a.a[row][col] % mod;
    int inv = power(a.a[row][col], mod - 2);
    for (int i = 0; i < n && inv; i++) {
      if (i != row && a.a[i][col]) {
        int x = (1LL * a.a[i][col] * inv) % mod;
        for (int j = col; j < n && x; j++) {
          if (a.a[row][j]) a.a[i][j] = (MODSQ + a.a[i][j] - 1LL * a.a[row][j] * x) % mod;
        }
      }
    }
    row++;
  }
  return det;
}