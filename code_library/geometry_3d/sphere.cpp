//  Spherical coordinates, distances, and sphere-sphere intersections.
P3 sph_pt(double r, double lat, double lon) {
  lat *= PI / 180; lon *= PI / 180;
  return P3(r * cos(lat) * cos(lon), r * cos(lat) * sin(lon), r * sin(lat));
}
double great_circle_dist(P3 o, double r, P3 a, P3 b) { return r * (a - o).angle(b - o); }
struct Sphere {
  P3 c; double r;
  double volume() const { return 4.0 / 3.0 * PI * r * r * r; }
  double surface_area() const { return 4 * PI * r * r; }
  // Line-Sphere Intersection Points
  vector<P3> inter(Line3D l) const {
    P3 proj = l.proj(c);
    double d2 = c.dist2(proj);
    if (d2 > r * r + EPS) return {};
    double h = sqrt(max(0.0, r * r - d2));
    P3 dir = l.d.unit();
    if (h < EPS) return {proj};
    return {proj - dir * h, proj + dir * h};
  }
  // if this point is inside the sphere
  bool contains(P3 p) const { return sgn(p.dist(c) - r) <= 0; }
  // Length of the tangent segment from an external point p (-1 if p is inside)
  double tangent_len(P3 p) const {
    double d = p.dist(c);
    return sgn(d - r) < 0 ? -1 : sqrt(max(0.0, d * d - r * r));
  }
  // Polar angle of the cap of tangency points from p (-1 if inside, -2 if on the surface)
  double tangent_angle(P3 p) const {
    double d = p.dist(c);
    if (sgn(d - r) < 0) return -1;
    if (sgn(d - r) == 0) return -2;
    return acos(r / d);
  }
};
// sphere-sphere intersection
pair<double, double> sphere_inter(Sphere s1, Sphere s2) {
  double d = s1.c.dist(s2.c);
  if (d >= s1.r + s2.r) return {0, 0};
  double R = max(s1.r, s2.r), r = min(s1.r, s2.r);
  double x = (R * R - r * r + d * d) / (2 * d);
  double h1 = R - x, h2 = (R + r - d) - h1;
  double vol = PI * h1 * h1 * (3 * R - h1) / 3.0 + PI * h2 * h2 * (3 * r - h2) / 3.0;
  double area = 2 * PI * R * h1 + 2 * PI * r * h2;
  return {area, vol};
}
// Radius of the circle in which two intersecting spheres meet
double sphere_inter_radius(Sphere s1, Sphere s2) {
  double d = s1.c.dist(s2.c), R = max(s1.r, s2.r), r = min(s1.r, s2.r);
  if (sgn(d - R - r) >= 0) return 0;
  double w = d * d - r * r + R * R;
  return sqrt(max(0.0, 4 * d * d * R * R - w * w)) / (2 * d);
}
// Sphere through four non-coplanar points
Sphere circum_sphere(P3 a, P3 b, P3 c, P3 d) {
  assert(sgn(Plane(a, b, c).side(d)) != 0);
  Plane u(a - b, (a + b) / 2), v(b - c, (b + c) / 2), w(c - d, (c + d) / 2);
  Line3D l1(u, v), l2(v, w);
  P3 o = line_closest(l1, l2);
  return {o, o.dist(a)};
}
// Center of the circle through three non-collinear coplanar points.
P3 circle_center(P3 a, P3 b, P3 c) {
  P3 v1 = b - a, v2 = c - a;
  double v11 = v1.dot(v1), v22 = v2.dot(v2), v12 = v1.dot(v2);
  double base = 0.5 / (v11 * v22 - v12 * v12);
  return a + v1 * (base * v22 * (v11 - v12)) + v2 * (base * v11 * (v22 - v12));
}
// approximate min enclosing sphere
Sphere min_sphere(vector<P3> p) {
  P3 c(0, 0, 0); int n = p.size(), pos = 0;
  for (auto &i : p) c = c + i;
  c = c / n;
  double ratio = 0.1;
  for (int it = 0; it < 100000; it++) {
    pos = 0;
    for (int i = 1; i < n; i++) if (c.dist2(p[i]) > c.dist2(p[pos])) pos = i;
    c = c + (p[pos] - c) * ratio;
    ratio *= 0.998;
  }
  return {c, c.dist(p[pos])};
}

