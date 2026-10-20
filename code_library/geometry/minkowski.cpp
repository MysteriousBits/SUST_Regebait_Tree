using P = Point<ld>;

void reorder(vector<P>& poly) {
  int pos = 0;
  for (int i = 1; i < (int)poly.size(); ++i)
    if (poly[i] < poly[pos]) pos = i;
  rotate(poly.begin(), poly.begin() + pos, poly.end());
}

vector<P> minkowski(vector<P> a, vector<P> b) {
  reorder(a), reorder(b);
  int n = a.size(), m = b.size(), ai = 0, bi = 0;
  a.push_back(a[0]), a.push_back(a[1]);
  b.push_back(b[0]), b.push_back(b[1]);
  vector<P> c;
  while (ai < n || bi < m) {
    c.push_back(a[ai] + b[bi]);
    if (ai < n && bi < m) {
      auto ori = (a[ai + 1] - a[ai]).cross(b[bi + 1] - b[bi]);
      if (ori > 1e-9) ai++;
      else if (ori < -1e-9) bi++;
      else ai++, bi++;
    } else if (ai < n) ai++;
    else bi++;
  }
  return c;
}

vector<P> minkowski_dif(vector<P> a, vector<P> b) {
  for (auto& p : b) p.x = -p.x, p.y = -p.y;
  return minkowski(a, b);
}