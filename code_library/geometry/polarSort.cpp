bool half(P p) {
  return p.y < 0 || (p.y == 0 && p.x < 0);
}
void polar_sort(vector<P>& v, P o = P(0, 0)) {
  sort(v.begin(), v.end(), [&](P a, P b) {
    P u = a - o, w = b - o;
    return make_tuple(half(u), 0.0, u.dist2()) < make_tuple(half(w), u.cross(w), w.dist2());
  });
}