vector<int> deriv(vector<int> a) {
  vector<int> res(max(1, (int)a.size() - 1));
  for (int i = 1; i < (int)a.size(); i++) res[i-1] = 1ll * a[i] * i % mod;
  return res;
}
vector<int> integr(vector<int> a) {
  vector<int> res(a.size() + 1);
  for (int i = 0; i < (int)a.size(); i++) 
    res[i+1] = 1ll * a[i] * POW(i + 1, mod - 2) % mod;
  return res;
}
vector<int> poly_log(vector<int> a, int n) {
  vector<int> res = integr(multiply(deriv(a), poly_inv(a, n)));
  res.resize(n); return res;
}
vector<int> poly_exp(vector<int> a, int n) {
  vector<int> b = {1};
  for (int len = 1; len < n; len *= 2) {
    b.resize(2 * len);
    vector<int> l = poly_log(b, 2 * len), sub(2 * len);
    sub[0] = (a[0] + 1 - l[0] + mod) % mod;
    for (int i = 1; i < 2 * len; i++) 
      sub[i] = ((i < a.size() ? a[i] : 0) - l[i] + mod) % mod;
    b = multiply(b, sub);
    b.resize(2 * len);
  }
  b.resize(n); return b;
}