typedef Point<double> P;
using Line = pair<P, P>;

bool bad(Line a, Line b, Line c) {
  auto res = lineInter(a.first, a.second, b.first, b.second);
  return res.first > 0 && sideOf(c.first, c.second, res.second, EPS) < 0;
}

vector<P> halfPlaneIntersection(vector<Line>& L) {
  auto ang = [](Line l) { return (l.second-l.first).angle(); };
  sort(all(L), [&](Line a,Line b) { return ang(a)<ang(b); });

  vector<Line> lines;
  for (int i = 0; i < L.size(); i++) {
    if (i && abs(ang(L[i])-ang(L[i-1]))<EPS) {
      if (sideOf(L[i].first,L[i].second,lines.back().first,EPS) < 0) {
        lines.pop_back(); lines.push_back(L[i]);
      }
    } else lines.push_back(L[i]);
  }
  int n = lines.size(), qf = 0, qb = 0;
  vector<Line> q(n);
  for (int i = 0; i < n; i++) {
    while (qb-qf >= 2 && bad(q[qb-1], q[qb-2], lines[i])) qb--;
    while (qb-qf >= 2 && bad(q[qf], q[qf+1], lines[i])) qf++;
    q[qb++] = lines[i];
  }
  while (qb-qf >= 3 && bad(q[qb-1], q[qb-2], q[qf])) qb--;
  while (qb-qf >= 3 && bad(q[qf], q[qf+1], q[qb-1])) qf++;
  if(qb-qf < 3) return {};

  vector<P> poly;
  for (int i = qf; i < qb; i++) {
    int nxt = (i+1 == qb) ? qf : i + 1;
    poly.push_back(lineInter(q[i].first, q[i].second, q[nxt].first, q[nxt].second).second);
  }
  return poly;
}
