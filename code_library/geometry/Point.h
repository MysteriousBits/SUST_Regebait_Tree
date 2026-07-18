template <class T>
int sgn(T x) {
  return (x > 0) - (x < 0);
  // return (x > EPS) - (x < -EPS); // for float
}
template <class T>
struct Point {
  typedef Point P;
  T x, y;
  explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
  bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
  bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); } // Use feq for float
  P operator+(P p) const { return P(x + p.x, y + p.y); }
  P operator-(P p) const { return P(x - p.x, y - p.y); }
  P operator*(T d) const { return P(x * d, y * d); }
  P operator/(T d) const { return P(x / d, y / d); }
  T dot(P p) const { return x * p.x + y * p.y; }
  T cross(P p) const { return x * p.y - y * p.x; }
  T cross(P a, P b) const { return (a - *this).cross(b - *this); }
  T dist2() const { return x * x + y * y; }
  T dist2(P p) const { return (*this - p).dist2(); }
  long double dist() const { return sqrt((long double)dist2()); }
  long double dist(P p) const { return (*this - p).dist(); }
  // angle to x-axis in interval [-pi, pi]
  long double angle() const { return atan2(y, x); }
  // Directed angle from vector 'this' to vector 'p' in interval [-pi, pi]
  long double angle(P p) const {
    return atan2((long double)this->cross(p), (long double)this->dot(p));
  }
  P unit() const { return *this / dist(); }  // makes dist()=1
  P perp() const { return P(-y, x); }        // rotates +90 degrees
  P normal() const { return perp().unit(); }
  // returns point rotated 'a' radians ccw around the origin
  P rotate(long double a) const {
    return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
  }
  // Project point 'p' onto the line formed by vector 'this' originating from origin
  P project(P p) const { return *this * ((long double)this->dot(p) / dist2()); }
  // Returns the signed length of the projection of vector 'p' onto vector 'this'
  long double scalar_project(P p) const { return (long double)this->dot(p) / dist(); }
  // Reflect point 'p' across the line formed by vector 'this' originating from origin
  P reflect(P p) const { return project(p) * 2 - p; }
  friend ostream& operator<<(ostream& os, P p) {
    return os << "(" << p.x << "," << p.y << ")";
  }
};