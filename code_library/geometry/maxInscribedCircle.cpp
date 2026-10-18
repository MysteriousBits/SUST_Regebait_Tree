ld maxInscribedCircle(vector<P>& poly) {
  ld lo = 0, hi = 1e6, ans = 0, L = 1e9;
  int n = poly.size();
  while (hi - lo >= 1e-12) {
    ld mid = lo + (hi - lo) / 2.0;
    vector<Line> l = {{{-L, -L}, {L, -L}}, {{L, -L}, {L, L}}, {{L, L}, {-L, L}}, {{-L, L}, {-L, -L}}};
    for (int i = 0; i < n; ++i) {
      auto a = poly[i], b = poly[(i + 1) % n];
      auto c = (b - a).unit().perp();
      l.push_back({a + c * mid, b + c * mid});
    }
    auto cur = halfPlaneIntersection(l);
    if (!cur.empty()) ans = lo = mid;
    else hi = mid;
  }
  return ans;
}