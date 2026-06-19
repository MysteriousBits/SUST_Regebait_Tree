const long long MOD = 998244353, root = 3;
void ntt(long long* x, long long* temp, long long* roots, int N, int skip) {
  if (N == 1) return;
  int n2 = N / 2;
  ntt(x, temp, roots, n2, skip * 2);
  ntt(x + skip, temp, roots, n2, skip * 2);
  for (int i = 0; i < N; i++) temp[i] = x[i * skip];
  for (int i = 0; i < n2; i++) {
    long long s = temp[2 * i], t = temp[2 * i + 1] * roots[skip * i];
    x[skip * i] = (s + t) % MOD;
    x[skip * (i + n2)] = ((s - t) % MOD + MOD) % MOD;
  }
}
void ntt(vector<long long>& x, bool inv = false) {
  long long e = modpow(root, (MOD - 1) / x.size(), MOD);
  if (inv) e = modpow(e, MOD - 2, MOD);
  vector<long long> roots(x.size(), 1), temp = roots;
  for (size_t i = 1; i < x.size(); i++) roots[i] = roots[i - 1]     * e % MOD;
  ntt(&x[0], &temp[0], &roots[0], x.size(), 1);
}
vector<long long> conv(vector<long long> a, vector<long long> b) {
  int s = a.size() + b.size() - 1;
  if (s <= 0) return {};
  int L = s > 1 ? 32 - __builtin_clz(s - 1) : 0, n = 1 << L;
  if (s <= 200) {
    vector<long long> c(s);
    for (size_t i = 0; i < a.size(); i++) {
      for (size_t j = 0; j < b.size(); j++) {
        c[i + j] = (c[i + j] + a[i] * b[j]) % MOD;
      }
    }
    return c;
  }
  a.resize(n); ntt(a);
  b.resize(n); ntt(b);
  vector<long long> c(n);
  long long d = modpow(n, MOD - 2, MOD);
  for (int i = 0; i < n; i++) c[i] = a[i] * b[i] % MOD * d % MOD;
  ntt(c, true);
  c.resize(s);
  return c;
}
vector<long long> mul(const vector<long long>& a, const vector<long long>& b, int n) {
  vector<long long> c = conv(a, b);
  if ((int)c.size() > n + 1) c.resize(n + 1);
  return c;
}
vector<long long> power(vector<long long> f, long long m, int n) {
  vector<long long> r = {1};
  if ((int)f.size() > n + 1) f.resize(n + 1);
  for (; m > 0; m >>= 1, f = mul(f, f, n))
  if (m & 1) r = mul(r, f, n);
  return r;
}