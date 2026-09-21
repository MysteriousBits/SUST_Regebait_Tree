// 3d line parametric form: `o + k * d`.
struct Line3D {
  P3 d, o;
  Line3D() {}
  Line3D(P3 p, P3 q) : d(q - p), o(p) {}
  Line3D(Plane p1, Plane p2) {
    d = p1.n.cross(p2.n);
    o = (p2.n * p1.d - p1.n * p2.d).cross(d) / d.dist2();
  }
  double dist2(P3 p) const { return d.cross(p - o).dist2() / d.dist2(); }
  double dist(P3 p) const { return sqrt(dist2(p)); }
  P3 proj(P3 p) const { return o + d * (d.dot(p - o) / d.dist2()); }
  P3 inter(Plane p) const { return o - d * (p.side(o) / d.dot(p.n)); }
  // Orthogonal reflection of point p across the line
  P3 reflect(P3 p) const { return proj(p) * 2 - p; }
  // Compare points by their projection on the line (use as a sort comparator)
  bool cmp_proj(P3 p, P3 q) const { return d.dot(p) < d.dot(q); }
  // Small angle between the direction vectors of two lines
  double angle(Line3D l) const { return d.small_angle(l.d); }
  bool is_para(Line3D l) const { return d.cross(l.d).dist() < EPS; }
  bool is_perp(Line3D l) const { return sgn(d.dot(l.d)) == 0; }
  // Distance from 3D segment [p, q] to point x
  static double seg_dist(P3 p, P3 q, P3 x) {
    if ((q - p).dot(x - p) < 0) return x.dist(p);
    if ((p - q).dot(x - q) < 0) return x.dist(q);
    return (q - p).unit().cross(x - p).dist();
  }
  // Check if point p lies on segment defined by [o, o + d]
  bool on_segment(P3 p) const {
    return dist(p) < EPS && (o - p).dot(o + d - p) <= EPS;
  }
};
// Line-line relations: min dist, closest point
double line_dist(Line3D l1, Line3D l2) {
  auto n = l1.d.cross(l2.d);
  if (n.dist2() == 0) return l1.dist(l2.o);
  return fabs((l2.o - l1.o).dot(n)) / n.dist();
}
P3 line_closest(Line3D l1, Line3D l2) {
  auto n2 = l2.d.cross(l1.d.cross(l2.d));
  return l1.o + l1.d * ((l2.o - l1.o).dot(n2) / l1.d.dot(n2));
}