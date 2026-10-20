ll multiplicative_order(ll a, ll mod) {
  if (__gcd(a, mod) != 1) return -1;
  ll m = totient(mod), p = m;
  ll ans = 2e18;
  if (power(a, p, mod) == 1) ans = p;
  vector<ll> fac;
  for (ll i = 2 ; i * i <= m; i++) {
    if (m % i == 0) {
      while(m % i == 0) m /= i, fac.push_back(i);
    }
  }
  if (m > 1) fac.push_back(m);
  for (auto x: fac) {
    if (power(a, p / x, mod) == 1) p /= x, ans = p;
  }
  assert(ans != 2e18);
  return ans;
}