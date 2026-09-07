ll fact[MAXN], finv[MAXN];
void calc_fact(ll m = MOD) {
  fact[0] = 1;
  for (int i = 1; i < MAXN; ++i) fact[i] = (fact[i - 1] * i) % m;
  finv[MAXN - 1] = inv(fact[MAXN - 1]);
  for (int i = MAXN - 2; i >= 0; --i) finv[i] = mul(finv[i + 1], i + 1);
}
ll C(int n, int k, ll m = MOD) {
  if (k > n) return 0;
  return mul(fact[n], mul(finv[k], finv[n - k]));
}