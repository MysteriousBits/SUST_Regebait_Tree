template <class P>
vector<P> circleSegmentIntersection(P c, double r, P a, P b) {
  P ab = b - a;
  double l2 = ab.dist2();
  if (l2 < 1e-12) return (a - c).dist() <= r + 1e-9 ? vector<P>{a} : vector<P>{};
  P p = a + ab * (c - a).dot(ab) / l2;
  double h2 = r * r - pow((c - a).cross(ab), 2) / l2;
  if (h2 < -1e-9) return {};
  P h = ab.unit() * sqrt(max(0.0, h2));
  vector<P> lpts = abs(h2) < 1e-9 ? vector<P>{p} : vector<P>{p - h, p + h}, res;
  for (auto &pt : lpts) {
    if ((a - pt).dot(b - pt) <= 1e-9) res.push_back(pt);
  }
  if (res.empty() && (a - c).dist() <= r + 1e-9 && (b - c).dist() <= r + 1e-9) {
    res = {a, b};
  }
  return res;
}