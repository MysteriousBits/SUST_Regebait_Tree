// Integer points on segment ab (excluding one endpoint; add +1 for both)
ll seg_b(P a, P b) { return gcd(abs(a.x - b.x), abs(a.y - b.y)); }

// Boundary integer points (B)
ll poly_b(const vector<P>& v) {
  ll b = 0; int n = v.size();
  for (int i = 0; i < n; ++i) b += seg_b(v[i], v[(i + 1) % n]);
  return b;
}
// Strictly interior integer points (I)
ll poly_i(const vector<P>& v) { return (area2(v) - poly_b(v) + 2) / 2; }