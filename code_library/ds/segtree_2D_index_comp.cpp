// USAGE
ST2D seg(n);
// Phase 1: register all (x, y) points that will ever be updated
for (auto& [x, y, v] : updates)
    seg.collect(1, 1, n, x, y);

// Phase 2: compress and allocate inner trees
seg.build(1, 1, n);

// Updates and queries
seg.upd   (1, 1, n, x, y, v);
seg.query (1, 1, n, x1, x2, y1, y2);
/////////////////////////////////////////
void compress(vector<int>& a) {
    sort(all(a));
    a.erase(unique(all(a)), a.end());
}
int ind(vi& a, int val) {
    return lower_bound(all(a), val) - a.begin();
}


struct ST2D {
  #define lc (nd << 1)
  #define rc ((nd << 1) | 1)

  int n;
  vector<vi> ys;       // compressed y-coords per x-node
  vector<vi> t;        // inner seg tree per x-node

  ST2D(int n) : n(n), ys(4 * n), t(4 * n) {}
  void collect(int nd, int b, int e, int x, int y) {
    ys[nd].pb(y);
    if (b == e) return;
    int mid = (b + e) >> 1;
    if (x <= mid) collect(lc, b, mid, x, y);
    else          collect(rc, mid + 1, e, x, y);
  }

  void build(int nd, int b, int e) {
    compress(ys[nd]);
    t[nd].assign(ys[nd].sz() * 2, 0);
    if (b == e) return;
    int mid = (b + e) >> 1;
    build(lc, b, mid);
    build(rc, mid + 1, e);
  }
  inline long long combine(long long a, long long b) { return max(a, b); }

  void upd_y(int nd, int y, long long v) {
    int m = ys[nd].sz();
    int i = ind(ys[nd], y) + m;
    t[nd][i] = combine(t[nd][i], v);
    for (i >>= 1; i >= 1; i >>= 1)
      t[nd][i] = combine(t[nd][i*2], t[nd][i*2+1]);
  }

  long long query_y(int nd, int y1, int y2) {
    if (y1 > y2) return 0;
    int m = ys[nd].sz();
    int l = ind(ys[nd], y1) + m;
    int r = (int)(upper_bound(all(ys[nd]), y2) - ys[nd].begin() - 1) + m;
    ll mx = 0;
    while (l <= r) {
        if (l%2 == 1) mx = combine(mx, t[nd][l++]);
        if (r%2 == 0) mx = combine(mx, t[nd][r--]);
        l >>= 1; r >>= 1;
    }
    return mx;
  }
  void upd(int nd, int b, int e, int x, int y, long long v) {
    upd_y(nd, y, v);
    if (b == e) return;
    int mid = (b + e) >> 1;
    if (x <= mid) upd(lc, b, mid, x, y, v);
    else          upd(rc, mid + 1, e, x, y, v);
  }

  long long query(int nd, int b, int e, int x1, int x2, int y1, int y2) {
    if (x1 > x2 || y1 > y2) return 0;  // empty range (e.g. a[i].f == 1)
    if (x1 > e  || b > x2)  return 0;
    if (x1 <= b && e <= x2)  return query_y(nd, y1, y2);
    int mid = (b + e) >> 1;
    return combine(query(lc, b, mid, x1, x2, y1, y2),
                   query(rc, mid+1, e, x1, x2, y1, y2));
}
};