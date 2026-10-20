using mint = modint<mod>;
// Finds the minimum linear recurrence transition vector
vector<mint> BerlekampMassey(vector<mint> S) {
  int n = (int)S.size(), L = 0, m = 0;
  vector<mint> C(n), B(n), T;
  C[0] = B[0] = 1;
  mint b = 1;
  for(int i = 0; i < n; i++) {
    ++m; mint d = S[i];
    for(int j = 1; j <= L; j++) d += C[j] * S[i - j];
    if (d == 0) continue;
    T = C; mint coef = d * b.inv();
    for(int j = m; j < n; j++) C[j] -= coef * B[j - m];
    if (2 * L > i) continue;
    L = i + 1 - L; B = T; b = d; m = 0;
  }
  C.resize(L + 1); C.erase(C.begin());
  for(auto &x: C) x *= -1;
  return C;
}
vector<mint> combine(int n, vector<mint> &a, vector<mint> &b, vector<mint> &tr) {
  vector<mint> res(n * 2 + 1, 0);
  for (int i = 0; i < n + 1; i++) {
    for (int j = 0; j < n + 1; j++) res[i + j] += a[i] * b[j];
  }
  for (int i = 2 * n; i > n; --i) {
    for (int j = 0; j < n; j++) res[i - 1 - j] += res[i] * tr[j];
  }
  res.resize(n + 1);
  return res;
}
// S contains initial terms, k is 0-indexed
mint LinearRecurrence(vector<mint> &S, vector<mint> &tr, long long k) {
  int n = S.size(); assert(n == (int)tr.size());
  if (n == 0) return 0;
  if (k < n) return S[k];
  vector<mint> pol(n + 1), e(pol);
  pol[0] = e[1] = 1;
  for (++k; k; k /= 2) {
    if (k % 2) pol = combine(n, pol, e, tr);
    e = combine(n, e, e, tr);
  }
  mint res = 0;
  for (int i = 0; i < n; i++) res += pol[i + 1] * S[i];
  return res;
}