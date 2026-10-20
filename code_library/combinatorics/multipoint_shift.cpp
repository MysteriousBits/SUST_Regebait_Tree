int fact[N], ifact[N];
vector<int> shift(vector<int> &f, int c) { //f(x + c)
  int n=(int)f.size();
  precompute(n + n - 1);
  vector<int> a = f; a.resize(lim);
  for (int i = 0; i < n; ++i) a[i] = (long long) a[i] * fact[i] % mod;
  reverse(a.begin(), a.begin()+n);
  vector<int> b; b.resize(lim); b[0] = 1;
  for (int i = 1; i < n; ++i) b[i] = (long long) b[i - 1] * c % mod;
  for (int i = 0; i < n; ++i) b[i] = (long long) b[i] * ifact[i] % mod;
  ntt(a, 1), ntt(b, 1);
  for (int i = 0; i < lim; ++i) a[i] = (long long) a[i] * b[i] % mod;
  ntt(a, 0), reverse(a.begin(), a.begin() + n);
  vector<int> g; g.resize(n);
  for (int i = 0; i < n; ++i) g[i] = (long long) a[i] * ifact[i] % mod;
  return g;
}