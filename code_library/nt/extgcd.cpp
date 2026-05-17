int extended_gcd(ll a, ll b, ll& x, ll& y) {
  if (!b) {
    x = 1, y = 0;
    return a;
  }
  ll g = extended_gcd(b, a % b, x, y);
  swap(x, y);
  y -= x * (a / b);
  return g;
}