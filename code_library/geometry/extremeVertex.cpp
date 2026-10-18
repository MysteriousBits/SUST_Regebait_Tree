
// id of the vertex having maximum dot product with z
// polygon must be convex
// top - upper right vertex
// for minimum dot product negate z and return -p[id].dot(z)
int extreme_vertex(const vector<P>& p, const P& z, const int top) { // O(log n)
  int n = p.size();
  if (n == 1) return 0;
  auto ans = p[0].dot(z);
  int id = 0;
  if (p[top].dot(z) > ans) ans = p[top].dot(z), id = top;
  int l = 1, r = top - 1;
  while (l < r) {
    int mid = (l + r) / 2;
    if (p[mid + 1].dot(z) >= p[mid].dot(z)) l = mid + 1;
    else r = mid;
  }
  if (p[l].dot(z) > ans) ans = p[l].dot(z), id = l;
  l = top + 1, r = n - 1;
  while (l < r) {
    int mid = (l + r) / 2;
    if (p[(mid + 1) % n].dot(z) >= p[mid].dot(z)) l = mid + 1;
    else r = mid;
  }
  l %= n;
  if (p[l].dot(z) > ans) ans = p[l].dot(z), id = l;
  return id;
}