ll fact[MAXN];
void calc_fact(ll mod = MOD) {
  fact[0] = 1;
  for (int i = 1; i < MAXN; ++i) {
    fact[i] = (fact[i - 1] * i) % mod;
  }
}
ll C(int n, int k, ll mod = MOD) {
  if (k > n) return 0;
  return (1LL * fact[n] * inv((1LL * fact[k] * fact[n - k]) % mod)) % mod;
}