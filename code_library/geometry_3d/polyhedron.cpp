// Converts 3D polygonal faces into flattened triangles: [T0_a, T0_b, T0_c, T1_a, ...]
vector<P3> flatten(const vector<vector<P3>> &fs) {
  vector<P3> p;
  for (auto &f : fs)
    for (size_t j = 1; j + 1 < f.size(); ++j)
      p.push_back(f[0]), p.push_back(f[j]), p.push_back(f[j + 1]);
  return p;
}
double poly_area(const vector<P3> &p) {
  double res = 0;
  for (size_t i = 0; i < p.size(); i += 3) res += (p[i + 1] - p[i]).cross(p[i + 2] - p[i]).dist();
  return res * 0.5;
}
double poly_volume(const vector<P3> &p) {
  P3 O(0, 0, 0); for (auto &pt : p) O = O + pt; O = O / p.size();
  double res = 0;
  for (size_t i = 0; i < p.size(); i += 3)
    res += fabs((p[i + 1] - p[i]).cross(p[i + 2] - p[i]).dot(p[i] - O));
  return res / 6.0;
}
P3 poly_centroid(const vector<P3> &p) {
  P3 O(0, 0, 0); for (auto &pt : p) O = O + pt; O = O / p.size();
  P3 c(0, 0, 0); double tv = 0;
  for (size_t i = 0; i < p.size(); i += 3) {
    double v = fabs((p[i + 1] - p[i]).cross(p[i + 2] - p[i]).dot(p[i] - O));
    c = c + (O + p[i] + p[i + 1] + p[i + 2]) * (v / 4.0);
    tv += v;
  }
  return c / tv;
}
bool contains(const vector<P3> &p, P3 pt) {
  P3 O(0, 0, 0); for (auto &pt_i : p) O = O + pt_i; O = O / p.size();
  for (size_t i = 0; i < p.size(); i += 3) {
    P3 n = (p[i + 1] - p[i]).cross(p[i + 2] - p[i]);
    if (n.dot(p[i] - O) < 0) n = n * -1.0; // Auto-flip to outward normal
    if (n.dot(pt - p[i]) > EPS) return false;
  }
  return true;
}
// Distance from point pt to the plane of face starting at index i
double pt_face_dist(const vector<P3> &p, size_t i, P3 pt) {
  P3 n = (p[i + 1] - p[i]).cross(p[i + 2] - p[i]);
  return fabs(n.dot(pt - p[i])) / n.dist();
}
// Returns total count of surface triangles
size_t num_tri(const vector<P3> &p) { return p.size() / 3; }
// Returns count of unique surface polygons by merging adjacent coplanar triangles
int num_poly(const vector<P3> &p) {
  int res = 0;
  for (size_t i = 0; i < p.size(); i += 3) {
    bool ok = true;
    for (size_t j = 0; j < i; j += 3) {
      P3 n = (p[j + 1] - p[j]).cross(p[j + 2] - p[j]);
      if (fabs(n.dot(p[i] - p[j])) < EPS && fabs(n.dot(p[i + 1] - p[j])) < EPS && fabs(n.dot(p[i + 2] - p[j])) < EPS) {
        ok = false; break;
      }
    }
    res += ok;
  }
  return res;
}