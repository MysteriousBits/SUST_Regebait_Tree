vector<P> polygonCut(const vector<P>& poly, P s, P e) {
  vector<P> res;
  for (int i = 0; i < (int)poly.size(); ++i) {
    P cur = poly[i], prev = i ? poly[i - 1] : poly.back();
    auto a = s.cross(e, cur), b = s.cross(e, prev);
    if ((a < 0) != (b < 0)) res.push_back(cur + (prev - cur) * (a / (a - b)));
    if (a < 0) res.push_back(cur);
  }
  return res;
}