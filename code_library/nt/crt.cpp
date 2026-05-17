ll modinv(ll a, ll m) {
  ll x, y;
  extended_gcd(a, m, x, y);
  x %= m;
  return x < 0 ? x + m : x;
}
ll crt(vector<pair<ll, ll>>& mods) {
  ll mod = 1;
  for (auto& p : mods) mod *= p.ss;
  ll ans = 0;
  for (auto [x, p] : mods) {
    ll m = mod / p;
    m = (m * modinv(m, p)) % mod;
    m = (m * x) % mod;
    ans = (ans + m) % mod;
  }
  return ans;
}