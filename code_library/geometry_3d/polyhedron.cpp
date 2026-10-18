double poly_area(const vector<vector<P3>> &fs) {
  vector<P3> p = flatten(reorient(fs));
  double res = 0;
  for (size_t i = 0; i + 2 < p.size(); i += 3) 
    res += (p[i + 1] - p[i]).cross(p[i + 2] - p[i]).dist();
  return res * 0.5;
}

double poly_volume(const vector<vector<P3>> &fs) {
  vector<P3> p = flatten(reorient(fs));
  if (p.empty()) return 0.0;
  P3 O(0, 0, 0); for (auto &pt : p) O = O + pt; O = O / p.size();
  double res = 0;
  for (size_t i = 0; i + 2 < p.size(); i += 3)
    res += (p[i + 1] - p[i]).cross(p[i + 2] - p[i]).dot(p[i] - O);
  return fabs(res) / 6.0;
}

P3 poly_centroid(const vector<vector<P3>> &fs) {
  vector<P3> p = flatten(reorient(fs));
  if (p.empty()) return P3(0, 0, 0);
  P3 O(0, 0, 0); for (auto &pt : p) O = O + pt; O = O / p.size();
  P3 c(0, 0, 0); double tv = 0;
  for (size_t i = 0; i + 2 < p.size(); i += 3) {
    double v = (p[i + 1] - p[i]).cross(p[i + 2] - p[i]).dot(p[i] - O);
    c = c + (O + p[i] + p[i + 1] + p[i + 2]) * (v / 4.0);
    tv += v;
  }
  return fabs(tv) < EPS ? O : c / tv;
}

bool contains(const vector<vector<P3>> &fs, P3 pt) {
  vector<P3> p = flatten(reorient(fs));
  if (p.empty()) return false;
  for (size_t i = 0; i + 2 < p.size(); i += 3) {
    P3 n = (p[i + 1] - p[i]).cross(p[i + 2] - p[i]);
    if (n.dot(pt - p[i]) > EPS) return false;
  }
  return true;
}

double pt_face_dist(const vector<vector<P3>> &fs, size_t i, P3 pt) {
  vector<P3> p = flatten(reorient(fs));
  if (i + 2 >= p.size()) return 0.0;
  P3 n = (p[i + 1] - p[i]).cross(p[i + 2] - p[i]);
  return fabs(n.dot(pt - p[i])) / n.dist();
}

size_t num_tri(const vector<vector<P3>> &fs) { 
  return flatten(reorient(fs)).size() / 3; 
}

int num_poly(const vector<vector<P3>> &fs) {
  vector<P3> p = flatten(reorient(fs));
  int res = 0;
  for (size_t i = 0; i + 2 < p.size(); i += 3) {
    bool ok = true;
    for (size_t j = 0; j < i; j += 3) {
      P3 n = (p[j + 1] - p[j]).cross(p[j + 2] - p[j]);
      if (fabs(n.dot(p[i] - p[j])) < EPS && 
          fabs(n.dot(p[i + 1] - p[j])) < EPS && 
          fabs(n.dot(p[i + 2] - p[j])) < EPS) {
        ok = false; break;
      }
    }
    res += ok;
  }
  return res;
}