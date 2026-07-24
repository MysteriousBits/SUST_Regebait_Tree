const int N = 3e5 + 9;
const double inf = 1e100;
const double PI = acos((double)-1.0);
const double eps = 1e-9;
// Returns -1 for negative, 0 for zero, 1 for positive (with epsilon tolerance)
int sign(double x) { return (x > eps) - (x < -eps); }
 
struct PT {
  double x, y;
  PT() { x = 0, y = 0; }
  PT(double x, double y) : x(x), y(y) {}
  PT(const PT &p) : x(p.x), y(p.y) {}
  
  PT operator + (const PT &a) const { return PT(x + a.x, y + a.y); }
  PT operator - (const PT &a) const { return PT(x - a.x, y - a.y); }
  PT operator * (const double a) const { return PT(x * a, y * a); }
  friend PT operator * (const double &a, const PT &b) { return PT(a * b.x, a * b.y); }
  PT operator / (const double a) const { return PT(x / a, y / a); }
  bool operator == (PT a) const { return sign(a.x - x) == 0 && sign(a.y - y) == 0; }
  bool operator != (PT a) const { return !(*this == a); }
  bool operator < (PT a) const { return sign(a.x - x) == 0 ? y < a.y : x < a.x; }
  bool operator > (PT a) const { return sign(a.x - x) == 0 ? y > a.y : x > a.x; }
  
  double norm() { return sqrt(x * x + y * y); }
  double norm2() { return x * x + y * y; }
  PT perp() { return PT(-y, x); }
  double arg() { return atan2(y, x); }
  
  // Returns a vector with norm r and having same direction
  PT truncate(double r) { 
    double k = norm();
    if (!sign(k)) return *this;
    r /= k;
    return PT(x * r, y * r);
  }
};
 
istream &operator >> (istream &in, PT &p) { return in >> p.x >> p.y; }
ostream &operator << (ostream &out, PT &p) { return out << "(" << p.x << "," << p.y << ")"; }
 
inline double dot(PT a, PT b) { return a.x * b.x + a.y * b.y; }
inline double dist2(PT a, PT b) { return dot(a - b, a - b); }
inline double dist(PT a, PT b) { return sqrt(dot(a - b, a - b)); }
inline double cross(PT a, PT b) { return a.x * b.y - a.y * b.x; }
inline double cross2(PT a, PT b, PT c) { return cross(b - a, c - a); }
inline int orientation(PT a, PT b, PT c) { return sign(cross(b - a, c - a)); }
 
PT perp(PT a) { return PT(-a.y, a.x); }
PT rotateccw90(PT a) { return PT(-a.y, a.x); }
PT rotatecw90(PT a) { return PT(a.y, -a.x); }
PT rotateccw(PT a, double t) { return PT(a.x * cos(t) - a.y * sin(t), a.x * sin(t) + a.y * cos(t)); }
PT rotatecw(PT a, double t) { return PT(a.x * cos(t) + a.y * sin(t), -a.x * sin(t) + a.y * cos(t)); }
 
double SQ(double x) { return x * x; }
double rad_to_deg(double r) { return (r * 180.0 / PI); }
double deg_to_rad(double d) { return (d * PI / 180.0); }
 
// Returns angle between vectors a and b in radians
double get_angle(PT a, PT b) {
  double costheta = dot(a, b) / a.norm() / b.norm();
  return acos(max((double)-1.0, min((double)1.0, costheta)));
}
 
struct line {
  PT a, b; // goes through points a and b
  PT v; double c; // line form: direction vec [cross] (x, y) = c 
  
  line() {}
  
  // Direction vector v and offset c
  line(PT v, double c) : v(v), c(c) {
    auto p = get_points();
    a = p.first; b = p.second;
  }
  
  // Equation ax + by + c = 0
  line(double _a, double _b, double _c) : v({_b, -_a}), c(-_c) {
    auto p = get_points();
    a = p.first; b = p.second;
  }
  
  // Goes through points p and q
  line(PT p, PT q) : v(q - p), c(cross(v, p)), a(p), b(q) {}
  
  // Extract any two points from this line
  pair<PT, PT> get_points() { 
    PT p, q; 
    double a_coef = -v.y, b_coef = v.x; // ax + by = c
    if (sign(a_coef) == 0) {
      p = PT(0, c / b_coef);
      q = PT(1, c / b_coef);
    } else if (sign(b_coef) == 0) {
      p = PT(c / a_coef, 0);
      q = PT(c / a_coef, 1);
    } else {
      p = PT(0, c / b_coef);
      q = PT(1, (c - a_coef) / b_coef);
    }
    return {p, q};
  }
  
  // Returns coefficients for ax + by + c = 0
  array<double, 3> get_abc() {
    double a_coef = -v.y, b_coef = v.x;
    return {a_coef, b_coef, -c};
  }
  
  // 1 if on the left, -1 if on the right, 0 if on the line
  int side(PT p) { return sign(cross(v, p) - c); }
  
  // Line that is perpendicular to this and goes through point p
  line perpendicular_through(PT p) { return {p, p + perp(v)}; }
  
  // Translate the line by vector t
  line translate(PT t) { return {v, c + cross(v, t)}; }
  
  // Compare two points by orthogonal projection on this line
  bool cmp_by_projection(PT p, PT q) { return dot(v, p) < dot(v, q); }
  
  line shift_left(double d) {
    PT z = v.perp().truncate(d);
    return line(a + z, b + z);
  }
};
 
// Minimum distance from point c to line through a and b
double dist_from_point_to_line(PT a, PT b, PT c) {
  return fabs(cross(b - a, c - a) / (b - a).norm());
}
 
// Returns true if point p is on line segment ab
bool is_point_on_seg(PT a, PT b, PT p) {
  if (fabs(cross(p - b, a - b)) < eps) {
    if (p.x < min(a.x, b.x) - eps || p.x > max(a.x, b.x) + eps) return false;
    if (p.y < min(a.y, b.y) - eps || p.y > max(a.y, b.y) + eps) return false;
    return true;
  }
  return false;
}
 
// Minimum distance point from point c to segment ab that lies on segment ab
PT project_from_point_to_seg(PT a, PT b, PT c) {
  double r = dist2(a, b);
  if (sign(r) == 0) return a;
  r = dot(c - a, b - a) / r;
  if (r < 0) return a;
  if (r > 1) return b;
  return a + (b - a) * r;
}
 
// Minimum distance from point c to segment ab
double dist_from_point_to_seg(PT a, PT b, PT c) {
  return dist(c, project_from_point_to_seg(a, b, c));
}
 
// 0 if not parallel, 1 if parallel, 2 if collinear
int is_parallel(PT a, PT b, PT c, PT d) {
  double k = fabs(cross(b - a, d - c));
  if (k < eps) {
    if (fabs(cross(a - b, a - c)) < eps && fabs(cross(c - d, c - a)) < eps) return 2;
    else return 1;
  } else return 0;
}
 
// 1 if point is ccw to the line, 2 if point is cw to the line, 3 if point is on the line
int point_line_relation(PT a, PT b, PT p) {
  int c = sign(cross(p - a, b - a));
  if (c < 0) return 1;
  if (c > 0) return 2;
  return 3;
}
 
// Intersection point between line ab and line cd assuming unique intersection exists
bool line_line_intersection(PT a, PT b, PT c, PT d, PT &ans) {
  double a1 = a.y - b.y, b1 = b.x - a.x, c1 = cross(a, b);
  double a2 = c.y - d.y, b2 = d.x - c.x, c2 = cross(c, d);
  double det = a1 * b2 - a2 * b1;
  if (det == 0) return 0;
  ans = PT((b1 * c2 - b2 * c1) / det, (c1 * a2 - a1 * c2) / det);
  return 1;
}
 
// Intersection point between segment ab and segment cd assuming unique intersection exists
bool seg_seg_intersection(PT a, PT b, PT c, PT d, PT &ans) {
  double oa = cross2(c, d, a), ob = cross2(c, d, b);
  double oc = cross2(a, b, c), od = cross2(a, b, d);
  if (oa * ob < 0 && oc * od < 0) {
    ans = (a * ob - b * oa) / (ob - oa);
    return 1;
  } else return 0;
}
 
// Custom change: Boolean intersection check (handles collinear overlap)
bool seg_seg_intersection(PT a, PT b, PT c, PT d) {
  double oa = cross2(c, d, a), ob = cross2(c, d, b);
  double oc = cross2(a, b, c), od = cross2(a, b, d);
  if (oa * ob < 0 && oc * od < 0) return true;
  
  // Checking orientation for very precise calculation
  if (oa == 0 && is_point_on_seg(c, d, a)) return true;
  if (ob == 0 && is_point_on_seg(c, d, b)) return true;
  if (oc == 0 && is_point_on_seg(a, b, c)) return true;
  if (od == 0 && is_point_on_seg(a, b, d)) return true;
  
  return false;
}
 
// 0 if do not intersect, 1 if proper intersect, 2 if segment intersect
int seg_line_relation(PT a, PT b, PT c, PT d) {
  double p = cross2(c, d, a);
  double q = cross2(c, d, b);
  if (sign(p) == 0 && sign(q) == 0) return 2;
  else if (p * q < 0) return 1;
  else return 0;
}
 
// Intersection between segament ab and line cd assuming unique intersection exists
bool seg_line_intersection(PT a, PT b, PT c, PT d, PT &ans) {
  bool k = seg_line_relation(a, b, c, d);
  assert(k != 2);
  if (k) line_line_intersection(a, b, c, d, ans);
  return k;
}
 
// Minimum distance from segment ab to segment cd
double dist_from_seg_to_seg(PT a, PT b, PT c, PT d) {
  PT dummy;
  if (seg_seg_intersection(a, b, c, d, dummy)) return 0.0;
  else return min({dist_from_point_to_seg(a, b, c), dist_from_point_to_seg(a, b, d), 
                   dist_from_point_to_seg(c, d, a), dist_from_point_to_seg(c, d, b)});
}
 
struct circle {
  PT p; double r;
  circle() {}
  circle(PT _p, double _r): p(_p), r(_r) {}
  circle(double x, double y, double _r): p(PT(x, y)), r(_r) {} // center (x, y) and radius r
  
  // Circumcircle of a triangle (three points must be unique)
  circle(PT a, PT b, PT c) {
    b = (a + b) * 0.5;
    c = (a + c) * 0.5;
    line_line_intersection(b, b + rotatecw90(a - b), c, c + rotatecw90(a - c), p);
    r = dist(a, p);
  }
  
  // Inscribed circle of a triangle (pass a bool just to differentiate from circumcircle)
  circle(PT a, PT b, PT c, bool t) {
    line u, v;
    double m = atan2(b.y - a.y, b.x - a.x), n = atan2(c.y - a.y, c.x - a.x);
    u.a = a;
    u.b = u.a + (PT(cos((n + m)/2.0), sin((n + m)/2.0)));
    v.a = b;
    m = atan2(a.y - b.y, a.x - b.x), n = atan2(c.y - b.y, c.x - b.x);
    v.b = v.a + (PT(cos((n + m)/2.0), sin((n + m)/2.0)));
    line_line_intersection(u.a, u.b, v.a, v.b, p);
    r = dist_from_point_to_seg(a, b, p);
  }
  
  bool operator == (circle v) { return p == v.p && sign(r - v.r) == 0; }
  double area() { return PI * r * r; }
  double circumference() { return 2.0 * PI * r; }
};
 
// 0 if outside, 1 if on circumference, 2 if inside circle
int circle_point_relation(PT p, double r, PT b) {
  double d = dist(p, b);
  if (sign(d - r) < 0) return 2;
  if (sign(d - r) == 0) return 1;
  return 0;
}
 
// 0 if outside, 1 if on circumference, 2 if inside circle
int circle_line_relation(PT p, double r, PT a, PT b) {
  double d = dist_from_point_to_line(a, b, p);
  if (sign(d - r) < 0) return 2;
  if (sign(d - r) == 0) return 1;
  return 0;
}
 
// Compute intersection of line through a and b with circle centered at c with radius r > 0
vector<PT> circle_line_intersection(PT c, double r, PT a, PT b) {
  vector<PT> ret;
  b = b - a; a = a - c;
  double A = dot(b, b), B = dot(a, b);
  double C = dot(a, a) - r * r, D = B * B - A * C;
  if (D < -eps) return ret;
  ret.push_back(c + a + b * (-B + sqrt(D + eps)) / A);
  if (D > eps) ret.push_back(c + a + b * (-B - sqrt(D)) / A);
  return ret;
}
 
// 5 - outside and do not intersect, 4 - intersect outside in one point
// 3 - intersect in 2 points, 2 - intersect inside in one point, 1 - inside and do not intersect
int circle_circle_relation(PT a, double r, PT b, double R) {
  double d = dist(a, b);
  if (sign(d - r - R) > 0) return 5;
  if (sign(d - r - R) == 0) return 4;
  double l = fabs(r - R);
  if (sign(d - r - R) < 0 && sign(d - l) > 0) return 3;
  if (sign(d - l) == 0) return 2;
  if (sign(d - l) < 0) return 1;
  assert(0); return -1;
}
 
vector<PT> circle_circle_intersection(PT a, double r, PT b, double R) {
  if (a == b && sign(r - R) == 0) return {PT(1e18, 1e18)};
  vector<PT> ret;
  double d = sqrt(dist2(a, b));
  if (d > r + R || d + min(r, R) < max(r, R)) return ret;
  double x = (d * d - R * R + r * r) / (2 * d);
  double y = sqrt(r * r - x * x);
  PT v = (b - a) / d;
  ret.push_back(a + v * x + rotateccw90(v) * y);
  if (y > 0) ret.push_back(a + v * x - rotateccw90(v) * y);
  return ret;
}
 
// Returns two circle c1, c2 through points a, b and of radius r
// 0 if there is no such circle, 1 if one circle, 2 if two circle
int get_circle(PT a, PT b, double r, circle &c1, circle &c2) {
  vector<PT> v = circle_circle_intersection(a, r, b, r);
  int t = v.size();
  if (!t) return 0;
  c1.p = v[0], c1.r = r;
  if (t == 2) c2.p = v[1], c2.r = r;
  return t;
}
 
// Returns area of intersection between two circles
double circle_circle_area(PT a, double r1, PT b, double r2) {
  double d = (a - b).norm();
  if (r1 + r2 < d + eps) return 0;
  if (r1 + d < r2 + eps) return PI * r1 * r1;
  if (r2 + d < r1 + eps) return PI * r2 * r2;
  double theta_1 = acos((r1 * r1 + d * d - r2 * r2) / (2 * r1 * d));
  double theta_2 = acos((r2 * r2 + d * d - r1 * r1) / (2 * r2 * d));
  return r1 * r1 * (theta_1 - sin(2 * theta_1) / 2.0) + r2 * r2 * (theta_2 - sin(2 * theta_2) / 2.0);
}
 
double area_of_triangle(PT a, PT b, PT c) {
  return fabs(cross(b - a, c - a) * 0.5);
}
 
// -1 if strictly inside, 0 if on the polygon, 1 if strictly outside
int is_point_in_triangle(PT a, PT b, PT c, PT p) {
  if (sign(cross(b - a, c - a)) < 0) swap(b, c);
  int c1 = sign(cross(b - a, p - a));
  int c2 = sign(cross(c - b, p - b));
  int c3 = sign(cross(a - c, p - c));
  if (c1 < 0 || c2 < 0 || c3 < 0) return 1;
  if (c1 + c2 + c3 != 3) return 0;
  return -1;
}
 
double area(vector<PT> &p) {
  double ans = 0; int n = p.size();
  for (int i = 0; i < n; i++) ans += cross(p[i], p[(i + 1) % n]);
  return fabs(ans) * 0.5;
}
 
// 0 if cw, 1 if ccw
bool get_direction(vector<PT> &p) {
  double ans = 0; int n = p.size();
  for (int i = 0; i < n; i++) ans += cross(p[i], p[(i + 1) % n]);
  if (sign(ans) > 0) return 1;
  return 0;
}
 
// Returns the convex hull of the set of points p (Monotone Chain)
vector<PT> convex_hull(vector<PT> &p) {
  if (p.size() <= 1) return p;
  vector<PT> v = p;
  sort(v.begin(), v.end());
  vector<PT> up, dn;
  for (auto& pt : v) {
    while (up.size() > 1 && orientation(up[up.size() - 2], up.back(), pt) >= 0) up.pop_back();
    while (dn.size() > 1 && orientation(dn[dn.size() - 2], dn.back(), pt) <= 0) dn.pop_back();
    up.push_back(pt);
    dn.push_back(pt);
  }
  v = dn;
  if (v.size() > 1) v.pop_back();
  reverse(up.begin(), up.end());
  up.pop_back();
  for (auto& pt : up) v.push_back(pt);
  if (v.size() == 2 && v[0] == v[1]) v.pop_back();
  return v;
}
 
// Checks if convex or not
bool is_convex(vector<PT> &p) {
  bool s[3] = {0, 0, 0};
  int n = p.size();
  for (int i = 0; i < n; i++) {
    int j = (i + 1) % n;
    int k = (j + 1) % n;
    s[sign(cross(p[j] - p[i], p[k] - p[i])) + 1] = 1;
    if (s[0] && s[2]) return 0;
  }
  return 1;
}
 
// -1 if strictly inside, 0 if on the polygon, 1 if strictly outside (O(log n))
int is_point_in_convex(vector<PT> &p, const PT& x) { 
  int n = p.size(); assert(n >= 3);
  int a = orientation(p[0], p[1], x), b = orientation(p[0], p[n - 1], x);
  if (a < 0 || b > 0) return 1;
  int l = 1, r = n - 1;
  while (l + 1 < r) {
    int mid = (l + r) >> 1;
    if (orientation(p[0], p[mid], x) >= 0) l = mid;
    else r = mid;
  }
  int k = orientation(p[l], p[r], x);
  if (k <= 0) return -k;
  if (l == 1 && a == 0) return 0;
  if (r == n - 1 && b == 0) return 0;
  return -1;
}
 
bool is_point_on_polygon(vector<PT> &p, const PT& z) {
  int n = p.size();
  for (int i = 0; i < n; i++) {
    if (is_point_on_seg(p[i], p[(i + 1) % n], z)) return 1;
  }
  return 0;
}
 
// Returns 1e9 if the point is on the polygon (O(n))
int winding_number(vector<PT> &p, const PT& z) { 
  if (is_point_on_polygon(p, z)) return 1e9;
  int n = p.size(), ans = 0;
  for (int i = 0; i < n; ++i) {
    int j = (i + 1) % n;
    bool below = p[i].y < z.y;
    if (below != (p[j].y < z.y)) {
      auto orient = orientation(z, p[j], p[i]);
      if (orient == 0) return 0;
      if (below == (orient > 0)) ans += below ? 1 : -1;
    }
  }
  return ans;
}
 
// -1 if strictly inside, 0 if on the polygon, 1 if strictly outside
int is_point_in_polygon(vector<PT> &p, const PT& z) { 
  int k = winding_number(p, z);
  return k == 1e9 ? 0 : k == 0 ? 1 : -1;
}
 
// id of the vertex having maximum dot product with z (O(log n))
int extreme_vertex(vector<PT> &p, const PT &z, const int top) { 
  int n = p.size();
  if (n == 1) return 0;
  double ans = dot(p[0], z); int id = 0;
  if (dot(p[top], z) > ans) ans = dot(p[top], z), id = top;
  int l = 1, r = top - 1;
  while (l < r) {
    int mid = (l + r) >> 1;
    if (dot(p[mid + 1], z) >= dot(p[mid], z)) l = mid + 1;
    else r = mid;
  }
  if (dot(p[l], z) > ans) ans = dot(p[l], z), id = l;
  l = top + 1, r = n - 1;
  while (l < r) {
    int mid = (l + r) >> 1;
    if (dot(p[(mid + 1) % n], z) >= dot(p[mid], z)) l = mid + 1;
    else r = mid;
  }
  l %= n;
  if (dot(p[l], z) > ans) ans = dot(p[l], z), id = l;
  return id;
}
 
pair<PT, int> point_poly_tangent(vector<PT> &p, PT Q, int dir, int l, int r) {
  while (r - l > 1) {
    int mid = (l + r) >> 1;
    bool pvs = orientation(Q, p[mid], p[mid - 1]) != -dir;
    bool nxt = orientation(Q, p[mid], p[mid + 1]) != -dir;
    if (pvs && nxt) return {p[mid], mid};
    if (!(pvs || nxt)) {
      auto p1 = point_poly_tangent(p, Q, dir, mid + 1, r);
      auto p2 = point_poly_tangent(p, Q, dir, l, mid - 1);
      return orientation(Q, p1.first, p2.first) == dir ? p1 : p2;
    }
    if (!pvs) {
      if (orientation(Q, p[mid], p[l]) == dir) r = mid - 1;
      else if (orientation(Q, p[l], p[r]) == dir) r = mid - 1;
      else l = mid + 1;
    }
    if (!nxt) {
      if (orientation(Q, p[mid], p[l]) == dir) l = mid + 1;
      else if (orientation(Q, p[l], p[r]) == dir) r = mid - 1;
      else l = mid + 1;
    }
  }
  pair<PT, int> ret = {p[l], l};
  for (int i = l + 1; i <= r; i++) {
    ret = orientation(Q, ret.first, p[i]) != dir ? make_pair(p[i], i) : ret;
  }
  return ret;
}
 
// (ccw, cw) tangents from a point that is outside this convex polygon
pair<int, int> tangents_from_point_to_polygon(vector<PT> &p, PT Q) {
  int ccw = point_poly_tangent(p, Q, 1, 0, (int)p.size() - 1).second;
  int cw = point_poly_tangent(p, Q, -1, 0, (int)p.size() - 1).second;
  return make_pair(ccw, cw);
}
 
// Minimum distance from a point to a convex polygon (assumes strictly outside)
double dist_from_point_to_polygon(vector<PT> &p, PT z) {
  double ans = inf;
  int n = p.size();
  if (n <= 3) {
    for(int i = 0; i < n; i++) ans = min(ans, dist_from_point_to_seg(p[i], p[(i + 1) % n], z));
    return ans;
  }
  auto [r, l] = tangents_from_point_to_polygon(p, z);
  if(l > r) r += n;
  while (l < r) {
    int mid = (l + r) >> 1;
    double left = dist2(p[mid % n], z), right= dist2(p[(mid + 1) % n], z);
    ans = min({ans, left, right});
    if(left < right) r = mid;
    else l = mid + 1;
  }
  ans = sqrt(ans);
  ans = min(ans, dist_from_point_to_seg(p[l % n], p[(l + 1) % n], z));
  ans = min(ans, dist_from_point_to_seg(p[l % n], p[(l - 1 + n) % n], z));
  return ans;
}
 
// Minimum distance from convex polygon p to line ab (O(log n))
double dist_from_polygon_to_line(vector<PT> &p, PT a, PT b, int top) { 
  PT orth = (b - a).perp();
  if (orientation(a, b, p[0]) > 0) orth = (a - b).perp();
  int id = extreme_vertex(p, orth, top);
  if (dot(p[id] - a, orth) > 0) return 0.0; // Intersects
  return dist_from_point_to_line(a, b, p[id]); // Does not intersect
}
 
// Minimum distance from a convex polygon to another convex polygon (O(n log n))
double dist_from_polygon_to_polygon(vector<PT> &p1, vector<PT> &p2) { 
  double ans = inf;
  for (int i = 0; i < p1.size(); i++) ans = min(ans, dist_from_point_to_polygon(p2, p1[i]));
  for (int i = 0; i < p2.size(); i++) ans = min(ans, dist_from_point_to_polygon(p1, p2[i]));
  return ans;
}
 
// Maximum distance from a convex polygon to another convex polygon (O(n))
double maximum_dist_from_polygon_to_polygon(vector<PT> &u, vector<PT> &v) { 
  int n = (int)u.size(), m = (int)v.size();
  double ans = 0;
  if (n < 3 || m < 3) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) ans = max(ans, dist2(u[i], v[j]));
    }
    return sqrt(ans);
  }
  if (u[0].x > v[0].x) swap(n, m), swap(u, v);
  int i = 0, j = 0, step = n + m + 10;
  while (j + 1 < m && v[j].x < v[j + 1].x) j++;
  while (step--) {
    if (cross(u[(i + 1)%n] - u[i], v[(j + 1)%m] - v[j]) >= 0) j = (j + 1) % m;
    else i = (i + 1) % n;
    ans = max(ans, dist2(u[i], v[j]));
  }
  return sqrt(ans);
}
 
// BUGFIX: Using 'double' instead of 'int' for coordinates to prevent precision loss.
double polygon_area(vector<PT>& v) {
  double calc_area = 0;
  int n = v.size();
  for(int i = 0; i < n; i++) {
    PT a = v[i], b = v[(i + 1) % n];
    double x1 = a.x, y1 = a.y; // Fixed from int
    double x2 = b.x, y2 = b.y; // Fixed from int
    calc_area += (x1 * y2 - x2 * y1);
  }
  return abs(calc_area) / 2.0; 
}
 
// WARNING: It's highly recommended to use the standard 'is_point_in_polygon()' 
// above instead of this custom one, since 'seg_seg_intersection' returns a boolean
// making `val == 1` or `val == 2` evaluations buggy.
int position_of_a_point_in_a_polygon(vector<PT>& v, PT c) {
  double xInf = inf, yInf = c.y + 1;
  PT d(xInf, yInf);
  int n = v.size();
  int cnt = 0;
  for(int i = 0; i < n; i++) {
    PT a = v[i], b = v[(i + 1) % n];
    // This relies on your overridden version of seg_seg_intersection which returns bool.
    bool intersect = seg_seg_intersection(a, b, c, d); 
    if (is_point_on_seg(a, b, c)) return 0; // BOUNDARY
    if (intersect) cnt++;
  }
  if (cnt % 2) return 1;    // INSIDE
  else return -1;           // OUTSIDE
}
 
// 0 -> collinear, 1 -> clockwise, 2 -> counter-clockwise
int getSign(int x1, int y1, int x2, int y2, int x3, int y3) {
  int direct = (y2 - y1) * (x3 - x2) - (y3 - y2) * (x2 - x1);
  if (direct > 0) return 1;     // clockWise
  if (direct < 0) return 2;     // counter - ClockWise
  return 0;                     // collinear
}
 
// 0 -> collinear, 1 -> clockwise, 2 -> counter-clockwise
int ori(int x1, int y1, int x2, int y2, int x3, int y3) {
  int val = (y2 - y1) * (x3 - x2) - (x2 - x1) * (y3 - y2);
  if (val == 0) return 0;       // collinear
  else if (val < 0) return 2;   // counter-clockwise
  return 1;                     // clockwise
}