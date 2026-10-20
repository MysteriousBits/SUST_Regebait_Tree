double rat(P a, P b) { return sgn(b.x) ? a.x / b.x : a.y / b.y; }

double polyUnion(vector<vector<P>>& poly) {
  double ret = 0;
  for (int i = 0; i < (int)poly.size(); ++i) for (int v = 0; v < (int)poly[i].size(); ++v) {
    P A = poly[i][v], B = poly[i][(v + 1) % (int)poly[i].size()];
    vector<pair<double, int>> segs = {{0, 0}, {1, 0}};
    for (int j = 0; j < (int)poly.size(); ++j) if (i != j) {
      for (int u = 0; u < (int)poly[j].size(); ++u) {
        P C = poly[j][u], D = poly[j][(u + 1) % (int)poly[j].size()];
        int sc = sideOf(A, B, C), sd = sideOf(A, B, D);
        if (sc != sd) {
          double sa = C.cross(D, A), sb = C.cross(D, B);
          if (min(sc, sd) < 0) segs.emplace_back(sa / (sa - sb), sgn(sc - sd));
        } else if (!sc && !sd && j < i && sgn((B - A).dot(D - C)) > 0) {
          segs.emplace_back(rat(C - A, B - A), 1);
          segs.emplace_back(rat(D - A, B - A), -1);
        }
      }
    }
    sort(segs.begin(), segs.end());
    for (auto& s : segs) s.first = min(max(s.first, 0.0), 1.0);
    double sum = 0;
    int cnt = segs[0].second;
    for (int j = 1; j < (int)segs.size(); ++j) {
      if (!cnt) sum += segs[j].first - segs[j - 1].first;
      cnt += segs[j].second;
    }
    ret += A.cross(B) * sum;
  }
  return ret / 2;
}