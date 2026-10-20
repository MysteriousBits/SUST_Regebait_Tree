ll fsum(ll n, ll m, ll a, ll b) {
  ll r = 0;
  if (a < 0) { ll a2 = (a % m + m) % m; r -= n * (n - 1) / 2 * ((a2 - a) / m); a = a2; }
  if (b < 0) { ll b2 = (b % m + m) % m; r -= n * ((b2 - b) / m); b = b2; }
  if (a >= m) { r += (n - 1) * n / 2 * (a / m); a %= m; }
  if (b >= m) { r += n * (b / m); b %= m; }
  ll y = (a * n + b) / m;
  if (!y) return r;
  ll x = y * m - b;
  return r + (n - (x + a - 1) / a) * y + fsum(y, a, m, (a - x % a) % a);
}