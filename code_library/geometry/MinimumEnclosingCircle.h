bool inside(const P& p, const P& c, double r) {
  return (p - c).dist() <= r + 1e-9;
}
// For generalized, udpate calc with gaussian elimination
pair<double, P> calc(const vector<P>& R) {
  if (R.empty()) return {0, P()};
  if (R.size() == 1) return {0, R[0]};
  P c = R.size() == 2 ? (R[0] + R[1]) / 2 : ccCenter(R[0], R[1], R[2]);
  return {(c - R[0]).dist(), c};
}

pair<double, P> welzl(vector<P>& p, vector<P>& R, int n, int D) {
  if (!n || R.size() == D + 1) return calc(R);
  auto res = welzl(p, R, n - 1, D);
  if (!inside(p[n - 1], res.second, res.first)) {
    R.push_back(p[n - 1]);
    res = welzl(p, R, n - 1, D);
    R.pop_back();
  }
  return res;
}

pair<double, P> mec(vector<P>& p, int D = 2) {
  shuffle(p.begin(), p.end(), mt19937(1337));
  vector<P> R;
  return welzl(p, R, p.size(), D);
}