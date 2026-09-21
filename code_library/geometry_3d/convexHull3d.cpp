// O(N^2) Incremental 3D Convex Hull builder (outputs flattened triangle vector)
struct CH3D {
  struct face { int a, b, c; bool ok; };
  size_t n, num;
  vector<P3> P;
  vector<face> F;
  vector<vector<int>> g;
  
  double dblcmp(P3 p, face f) { return ((P[f.b] - P[f.a]).cross(P[f.c] - P[f.a])).dot(p - P[f.a]); }
  void deal(int p, int a, int b) {
    int f = g[a][b];
    if (F[f].ok) {
      if (dblcmp(P[p], F[f]) > EPS) dfs(p, f);
      else {
        g[p][b] = g[a][p] = g[b][a] = num;
        F[num++] = {b, a, p, true};
      }
    }
  }
  void dfs(int p, int now) {
    F[now].ok = false;
    deal(p, F[now].b, F[now].a);
    deal(p, F[now].c, F[now].b);
    deal(p, F[now].a, F[now].c);
  }
  vector<P3> build(vector<P3> p) {
    P = p; n = P.size(); num = 0;
    if (n < 4) return {};
    F.resize(8 * n + 1); g.assign(n + 1, vector<int>(n + 1, 0));

    bool ok = false;
    for (size_t i = 1; i < n; ++i) if (P[0].dist(P[i]) > EPS) { swap(P[1], P[i]); ok = true; break; }
    if (!ok) return {}; ok = false;
    for (size_t i = 2; i < n; ++i) if ((P[0] - P[1]).cross(P[1] - P[i]).dist() > EPS) { swap(P[2], P[i]); ok = true; break; }
    if (!ok) return {}; ok = false;
    for (size_t i = 3; i < n; ++i) if (fabs(((P[0] - P[1]).cross(P[1] - P[2])).dot(P[0] - P[i])) > EPS) { swap(P[3], P[i]); ok = true; break; }
    if (!ok) return {};

    for (int i = 0; i < 4; ++i) {
      face add = {(i + 1) % 4, (i + 2) % 4, (i + 3) % 4, true};
      if (dblcmp(P[i], add) > 0) swap(add.b, add.c);
      g[add.a][add.b] = g[add.b][add.c] = g[add.c][add.a] = num;
      F[num++] = add;
    }
    for (size_t i = 4; i < n; ++i)
      for (size_t j = 0; j < num; ++j) if (F[j].ok && dblcmp(P[i], F[j]) > EPS) { dfs(i, j); break; }

    vector<P3> res;
    for (size_t i = 0; i < num; ++i) if (F[i].ok) {
      res.push_back(P[F[i].a]); res.push_back(P[F[i].b]); res.push_back(P[F[i].c]);
    }
    return res;
  }
};