ll inverse(ll a, ll m) {
  ll x, y;
  ll g = extgcd(a, m, x, y);
  if (g != 1) return -1;
  return (x % m + m) % m;
}
// returns n! % mod without taking all the multiple factors of p into account that appear in the factorial
// mod = multiple of p
// O(mod) * log(n)
int factmod(ll n, int p, const int mod) {
  vector<int> f(mod + 1);
  f[0] = 1 % mod;
  for (int i = 1; i <= mod; i++) {
    if (i % p) f[i] = 1LL * f[i - 1] * i % mod;
    else f[i] = f[i - 1];
  }
  int ans = 1 % mod;
  while (n > 1) {
    ans = 1LL * ans * f[n % mod] % mod;
    ans = 1LL * ans * power(f[mod], n / mod, mod) % mod;
    n /= p;
  }
  return ans; 
}
ll multiplicity(ll n, int p) {
  //legendra
  ll ans = 0;
  while (n) n /= p, ans += n;
  return ans;
}
// C(n, r) modulo p^k
// O(p^k log n)
int ncr(ll n, ll r, int p, int k) {
  if (n < r or r < 0) return 0;
  int mod = 1;
  for (int i = 0; i < k; i++) mod *= p; 
  ll t = multiplicity(n, p) - multiplicity(r, p) - multiplicity(n - r, p);
  if (t >= k) return 0;
  int ans = 1LL * factmod(n, p, mod) * inverse(factmod(r, p, mod), mod) % mod * inverse(factmod(n - r, p, mod), mod) % mod;
  ans = 1LL * ans * power(p, t, mod) % mod;
  return ans;
}