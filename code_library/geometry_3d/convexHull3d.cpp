// O(N^2) Incremental 3D Convex Hull builder (outputs flattened triangle vector)
struct CH3D {
  struct face { int a, b, c; bool ok; };
  int n, num;
  vector<P3> P;
  vector<face> F;
  vector<vector<int>> g;
 
  void init(vector<P3> p) {
    P = p; n = p.size(); num = 0;
    F.resize(8 * n + 1); g.assign(n + 1, vector<int>(n + 1, 0));
  }
  double volume(P3 a, P3 b, P3 c, P3 d) { return ((b - a).cross(c - a)).dot(d - a); }
  double dblcmp(P3 &p, face &f) { return ((P[f.b] - P[f.a]).cross(P[f.c] - P[f.a])).dot(p - P[f.a]); }
 
  void deal(int p, int a, int b) {
    int f = g[a][b]; face add;
    if (F[f].ok) {
      if (dblcmp(P[p], F[f]) > EPS) dfs(p, f);
      else {
        add = {b, a, p, true};
        g[p][b] = g[a][p] = g[b][a] = num;
        F[num++] = add;
      }
    }
  }
  void dfs(int p, int now) {
    F[now].ok = false;
    deal(p, F[now].b, F[now].a);
    deal(p, F[now].c, F[now].b);
    deal(p, F[now].a, F[now].c);
  }
  void build() {
    if (n < 4) return;
    bool ok = false;
    for (int i = 1; i < n; i++) if (P[0].dist(P[i]) > EPS) { swap(P[1], P[i]); ok = true; break; }
    if (!ok) return; ok = false;
    for (int i = 2; i < n; i++) if ((P[0] - P[1]).cross(P[1] - P[i]).dist() > EPS) { swap(P[2], P[i]); ok = true; break; }
    if (!ok) return; ok = false;
    for (int i = 3; i < n; i++) if (fabs(((P[0] - P[1]).cross(P[1] - P[2])).dot(P[0] - P[i])) > EPS) { swap(P[3], P[i]); ok = true; break; }
    if (!ok) return;
 
    for (int i = 0; i < 4; i++) {
      face add = {(i + 1) % 4, (i + 2) % 4, (i + 3) % 4, true};
      if (dblcmp(P[i], add) > 0) swap(add.b, add.c);
      g[add.a][add.b] = g[add.b][add.c] = g[add.c][add.a] = num;
      F[num++] = add;
    }
    for (int i = 4; i < n; i++) {
      for (int j = 0; j < num; j++) if (F[j].ok && dblcmp(P[i], F[j]) > EPS) { dfs(i, j); break; }
    }
    int tmp = num; num = 0;
    for (int i = 0; i < tmp; i++) if (F[i].ok) F[num++] = F[i];
  }
  // center of mass
  P3 centroid() {
    P3 ans(0, 0, 0), o(0, 0, 0); double all = 0;
    for (int i = 0; i < num; i++) {
      double vol = volume(o, P[F[i].a], P[F[i].b], P[F[i].c]);
      ans = ans + (o + P[F[i].a] + P[F[i].b] + P[F[i].c]) / 4.0 * vol;
      all += vol;
    }
    return ans / all;
  }
  // Total surface area of the 3D Convex Hull
  double area() {
    if (n == 3) return (P[1] - P[0]).cross(P[2] - P[0]).dist() * 0.5;
    double res = 0;
    for (int i = 0; i < num; i++) {
      res += (P[F[i].b] - P[F[i].a]).cross(P[F[i].c] - P[F[i].a]).dist();
    }
    return res * 0.5;
  }
  // Total volume enclosed by the 3D Convex Hull
  double volume() {
    double res = 0; P3 o(0, 0, 0);
    for (int i = 0; i < num; i++) res += volume(o, P[F[i].a], P[F[i].b], P[F[i].c]);
    return fabs(res / 6.0);
  }
  // Are the triangular faces s and t coplanar?
  bool same(int s, int t) {
    P3 a = P[F[s].a], b = P[F[s].b], c = P[F[s].c];
    return fabs(volume(a, b, c, P[F[t].a])) < EPS && fabs(volume(a, b, c, P[F[t].b])) < EPS &&
           fabs(volume(a, b, c, P[F[t].c])) < EPS;
  }
  int num_tri() { return num; } // number of surface triangles
  int num_poly() {              // number of surface polygons, O(num^2)
    int res = 0;
    for (int i = 0; i < num; i++) {
      bool ok = true;
      for (int j = 0; j < i; j++) if (same(i, j)) { ok = false; break; }
      res += ok;
    }
    return res;
  }
  // Distance from point p to the plane of face i
  double pt_face_dist(P3 p, int i) {
    return fabs(volume(P[F[i].a], P[F[i].b], P[F[i].c], p)) /
           (P[F[i].b] - P[F[i].a]).cross(P[F[i].c] - P[F[i].a]).dist();
  }
  // Check if point p is inside or on the 3D Convex Hull
  bool contains(P3 p) {
    for (int i = 0; i < num; i++) {
      if (dblcmp(p, F[i]) > EPS) return false;
    }
    return true;
  }
};