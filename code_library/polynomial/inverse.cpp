vector<int> poly_inv(vector<int> a, int n) {
  vector<int> b = {POW(a[0], mod - 2)};
  for (int len = 1; len < n; len *= 2) {
    vector<int> a_cut(a.begin(), a.begin() + min((int)a.size(), 2 * len));
    vector<int> x = multiply(b, b);
    x = multiply(x, a_cut);
    b.resize(2 * len);
    for (int i = 0; i < 2 * len; i++)
      b[i] = (2ll * b[i] - x[i] + mod) % mod;
  }
  b.resize(n); return b;
}