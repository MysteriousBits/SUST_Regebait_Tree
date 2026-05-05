// USAGE
ST2D sg(NX, NY); // dimensions 1..NX, 1..NY
sg.upd   (1, 1, NX, x, y, v);
sg.query (1, 1, NX, x1, x2, y1, y2);

struct ST2D {
  #define lc (nd << 1)
  #define rc ((nd << 1) | 1)
  #define lcy (ndy << 1)
  #define rcy ((ndy << 1) | 1)

  int NX, NY;
  vector<vector<long long>> t;

  ST2D(int NX, int NY) : NX(NX), NY(NY), t(4 * NX, vector<long long>(4 * NY, 0)) {}

  inline long long combine(long long a, long long b) { return max(a, b); }

  inline void pull_y(int nd, int ndy) {
    t[nd][ndy] = combine(t[nd][lcy], t[nd][rcy]);
  }
  inline void pull_x(int nd, int ndy) {
    t[nd][ndy] = combine(t[lc][ndy], t[rc][ndy]);
  }

  // -------------------------
  // Inner seg tree on y-axis
  // -------------------------
  void upd_y(int nd, int ndy, int by, int ey, int j, long long v, bool leaf_x) {
    if (by == ey) {
      if (leaf_x) t[nd][ndy] = v;
      else        t[nd][ndy] = combine(t[lc][ndy], t[rc][ndy]);
      return;
    }
    int mid = (by + ey) >> 1;
    if (j <= mid) upd_y(nd, lcy, by, mid, j, v, leaf_x);
    else          upd_y(nd, rcy, mid+1, ey, j, v, leaf_x);
    pull_y(nd, ndy);
  }

  long long query_y(int nd, int ndy, int by, int ey, int y1, int y2) {
    if (y1 > ey || by > y2) return 0;
    if (y1 <= by && ey <= y2) return t[nd][ndy];
    int mid = (by + ey) >> 1;
    return combine(query_y(nd, lcy, by, mid, y1, y2),
                   query_y(nd, rcy, mid+1, ey, y1, y2));
  }

  // -------------------------
  // Outer seg tree on x-axis
  // -------------------------
  void upd(int nd, int bx, int ex, int i, int j, long long v) {
    if (bx == ex) {
      upd_y(nd, 1, 1, NY, j, v, true);
      return;
    }
    int mid = (bx + ex) >> 1;
    if (i <= mid) upd(lc, bx, mid, i, j, v);
    else          upd(rc, mid+1, ex, i, j, v);
    upd_y(nd, 1, 1, NY, j, v, false);  // pull x into inner nodes
  }

  long long query(int nd, int bx, int ex, int x1, int x2, int y1, int y2) {
    if (x1 > ex || bx > x2) return 0;
    if (x1 <= bx && ex <= x2) return query_y(nd, 1, 1, NY, y1, y2);
    int mid = (bx + ex) >> 1;
    return combine(query(lc, bx, mid, x1, x2, y1, y2),
                   query(rc, mid+1, ex, x1, x2, y1, y2));
  }
};