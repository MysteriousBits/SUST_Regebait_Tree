// Tetrahedron (A, B, C, D)
double vol_tetrahedron(p3 a, p3 b, p3 c, p3 d) { 
  return fabs((b - a).cross(c - a).dot(d - a)) / 6.0; 
}