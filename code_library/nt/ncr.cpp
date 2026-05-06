ll fact[MAXN];
void calc_fact(ll m = MOD) {
  fact[0] = 1;
  for (int i = 1; i < MAXN; ++i) {
    fact[i] = (fact[i - 1] * i) % m;
  }
}
ll C(int n, int k, ll m = MOD) {
  if (k > n) return 0;
  return dvd(fact[n], fact[k] * fact[n - k] % m, m);
}