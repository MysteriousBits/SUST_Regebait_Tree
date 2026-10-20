using P2 = Point<double>;
struct P3 {
  double x, y, z;
  explicit P3(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
  bool operator<(P3 p) const { return tie(x, y, z) < tie(p.x, p.y, p.z); }
  bool operator==(P3 p) const { return tie(x, y, z) == tie(p.x, p.y, p.z); }
  P3 operator+(P3 p) const { return P3(x + p.x, y + p.y, z + p.z); }
  P3 operator-(P3 p) const { return P3(x - p.x, y - p.y, z - p.z); }
  P3 operator*(double d) const { return P3(x * d, y * d, z * d); }
  P3 operator/(double d) const { return P3(x / d, y / d, z / d); }
  double dot(P3 p) const { return x * p.x + y * p.y + z * p.z; }
  P3 cross(P3 p) const { return P3(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x); }
  double dist2() const { return x * x + y * y + z * z; }
  double dist2(P3 p) const { return (*this - p).dist2(); }
  double dist() const { return sqrt(dist2()); }
  double dist(P3 p) const { return (*this - p).dist(); }
  P3 unit() const { return *this / dist(); }
  double angle(P3 p) const { return atan2(cross(p).dist(), dot(p)); }
  // (this*a).b
  double triple(P3 a, P3 b) const { return cross(a).dot(b); }
  // Smallest angle between this and p, ignoring direction, in [0, PI/2]
  double small_angle(P3 p) const { return acos(min(fabs(dot(p)) / dist() / p.dist(), 1.0)); }
  // Same direction, length r 
  P3 truncate(double r) const { double k = dist(); return !sgn(k) ? *this : *this * (r / k); }
  // Rotate vector around unit axis 'u' by angle 'a' (Rodrigues' rotation formula)
  P3 rotate(P3 u, double a) const {
    u = u.unit();
    return *this * cos(a) + u.cross(*this) * sin(a) + u * u.dot(*this) * (1 - cos(a));
  }
  // Returns an arbitrary orthogonal unit vector to this
  P3 perp() const { return fabs(x) > EPS || fabs(y) > EPS ? P3(-y, x, 0).unit() : P3(0, -z, y).unit(); }
};
 // orient` is >0 if s lies on lies on the same side of plane pqr as (q-p) x (r-p), <0 opposite, 0 on it.
 // orient_by_normal: 2D-like orientation of p->q->r on the plane with normal n.
double orient(P3 p, P3 q, P3 r, P3 s) { return (q - p).cross(r - p).dot(s - p); }
double orient_by_normal(P3 p, P3 q, P3 r, P3 n) { return (q - p).cross(r - p).dot(n); }
