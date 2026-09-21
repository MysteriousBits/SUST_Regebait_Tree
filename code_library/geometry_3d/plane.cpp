// 3D Plane: normal n, offset d (n.dot(p) = d)
struct Plane {
  P3 n; double d;
  Plane(P3 n, double d) : n(n), d(d) {}
  Plane(P3 n, P3 p) : n(n), d(n.dot(p)) {}
  Plane(P3 p, P3 q, P3 r) : Plane((q - p).cross(r - p), p) {}
  double side(P3 p) const { return n.dot(p) - d; }
  double dist(P3 p) const { return fabs(side(p)) / n.dist(); }
  P3 proj(P3 p) const { return p - n * (side(p) / n.dist2()); }
  P3 reflect(P3 p) const { return p - n * (2 * side(p) / n.dist2()); }
  // [-PI, PI]
  double angle(Plane p) const { return n.angle(p.n); }
  // [0, PI/2]
  double small_angle(Plane p) const { return n.small_angle(p.n); }
  bool is_para(Plane p) const { return n.cross(p.n).dist() < EPS; }
  bool is_perp(Plane p) const { return sgn(n.dot(p.n)) == 0; }
  // Translate the plane by vector t
  Plane translate(P3 t) const { return {n, d + n.dot(t)}; }
  // Shift the plane along n by distance dis
  Plane shift_up(double dis) const { return {n, d + dis * n.dist()}; }
  // Two distinct points lying on the plane (n must be non-zero)
  pair<P3, P3> two_pts() const {
    int sx = sgn(n.x), sy = sgn(n.y), sz = sgn(n.z);
    assert(sx || sy || sz);
    if (!sx && !sy) return {P3(1, 0, d / n.z), P3(0, 1, d / n.z)};
    if (!sy && !sz) return {P3(d / n.x, 1, 0), P3(d / n.x, 0, 1)};
    if (!sz && !sx) return {P3(1, d / n.y, 0), P3(0, d / n.y, 1)};
    if (!sx) return {P3(1, d / n.y, 0), P3(0, 0, d / n.z)};
    if (!sy) return {P3(0, 1, d / n.z), P3(d / n.x, 0, 0)};
    if (!sz) return {P3(d / n.x, 0, 1), P3(0, d / n.y, 0)};
    if (sgn(d)) return {P3(d / n.x, 0, 0), P3(0, d / n.y, 0)};
    return {P3(n.y, -n.x, 0), P3(-n.y, n.x, 0)};
  }
};
// Intersection line of two planes 3-point pairs.
pair<P3, P3> plane_inter(P3 a1, P3 b1, P3 c1, P3 a2, P3 b2, P3 c2) {
  auto n1 = (b1 - a1).cross(c1 - a1), n2 = (b2 - a2).cross(c2 - a2);
  auto d = n1.cross(n2);
  if (d.dist2() == 0) return {P3(), P3()};
  auto o = (n2 * n1.dot(a1) - n1 * n2.dot(a2)).cross(d) / d.dist2();
  return {o, o + d};
}
