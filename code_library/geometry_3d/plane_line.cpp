
// Plane-line angles, relations, and perpendiculars through a point.
double angle(Plane p, Line3D l) { return PI / 2 - p.n.small_angle(l.d); }
bool is_para(Plane p, Line3D l) { return sgn(p.n.dot(l.d)) == 0; }
bool is_perp(Plane p, Line3D l) { return p.n.cross(l.d).dist() < EPS; }
Line3D perp_through(Plane p, P3 o) { return Line3D(o, o + p.n); }
Plane perp_through(Line3D l, P3 o) { return Plane(l.d, o); }