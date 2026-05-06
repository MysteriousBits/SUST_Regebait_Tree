inline ll mod(ll n, ll m = MOD) { return (m + n % m) % m; }
ll modpow(ll n, ll k, ll m = MOD) {
  ll ret = 1;
  n = mod(n, m);
  while (k) {
    if (k & 1) ret = (ret * n) % m;
    n = (n * n) % m;
    k >>= 1;
  }
  return ret;
}
inline ll inv(ll n, ll m = MOD) { return modpow(n, m - 2, m); }
inline ll mul(ll x, ll y, ll m = MOD) { return (mod(x, m) * mod(y, m)) % m; }
inline ll dvd(ll x, ll y, ll m = MOD) { return mul(x, inv(y, m), m); }