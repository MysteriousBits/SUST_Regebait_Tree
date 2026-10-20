struct FT2D {
  int n, m; vector<vector<ll>> s;
  FT2D(int n, int m) : n(n + 1), m(m + 1), s(n + 1, vector<ll>(m + 1)) {}
  FT2D(int n) : FT2D(n, n) {}
  void update(int x, int y, ll dif) {
    for (int i = x; i < n; i += i & -i)
      for (int j = y; j < m; j += j & -j) s[i][j] += dif;
  }
  ll query(int x, int y) {
    ll res = 0;
    for (int i = x; i > 0; i -= i & -i)
      for (int j = y; j > 0; j -= j & -j) res += s[i][j];
    return res;
  }
  ll query(int x1, int y1, int x2, int y2) {
    return query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
  }
};