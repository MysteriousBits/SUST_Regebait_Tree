bool merge(ll a1, ll m1, ll a2, ll m2, ll &res, ll &mod) {
  ll x, y, g = extgcd(m1, m2, x, y);
  if ((a2 - a1) % g != 0) return false;
  
  ll m2g = m2 / g;
  ll t = (ll)((__int128)((a2 - a1) / g % m2g) * (x % m2g) % m2g);
  if (t < 0) t += m2g;
  
  __int128 lcm_mod = (__int128)(m1 / g) * m2;
  __int128 tmp = (__int128)a1 + (__int128)m1 * t;
  
  res = (ll)(tmp % lcm_mod);
  if (res < 0) res += (ll)lcm_mod;
  mod = (ll)lcm_mod;
  return true;
}