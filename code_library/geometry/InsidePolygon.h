bool is_point_on_polygon(vector<P> &p, P& z) {
    int n = p.size();
    for (int i = 0; i < n; i++) {
    	if (onSegment(p[i], p[(i + 1) % n], z)) return 1;
    }
    return 0;
}
int winding_number(vector<P>& p, P& z) { // O(n)
  if (is_point_on_polygon(p, z)) return 1e9;
  int n = p.size(), ans = 0;
  for (int i = 0; i < n; ++i) {
    int j = (i + 1) % n;
    bool below = p[i].y < z.y;
    if (below != (p[j].y < z.y)) {
      auto orient = z.cross(p[j], p[i]);
      if (abs(orient) < 1e-9) return 0;
      if (below == (orient > 0)) ans += below ? 1 : -1;
    }
  }
  return ans;
}
// -1 if strictly inside, 0 if on the polygon, 1 if strictly outside
int is_point_in_polygon(vector<P>& p,  P& z) { // O(n)
  int k = winding_number(p, z);
  return k == 1e9 ? 0 : k == 0 ? 1 : -1;
}