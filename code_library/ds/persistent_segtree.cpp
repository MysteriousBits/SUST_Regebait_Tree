struct PST {
#define lc t[cur].l
#define rc t[cur].r
  struct node {
    int l = 0, r = 0, val = 0;
  } t[40 * N];
  int T = 0;
  int combine(int a, int b) { return a + b; } // change
  void pull(int cur) { t[cur].val = combine(t[lc].val, t[rc].val); }
  int build(int b, int e) {
    int cur = ++T;
    if (b == e) return cur;
    int mid = b + e >> 1;
    lc = build(b, mid);
    rc = build(mid + 1, e);
    pull(cur);
    return cur;
  }
  // Build tree from initial vector
  int build(int b, int e, const vector<int>& a) {
    int cur = ++T;
    if (b == e) {
      t[cur].val = a[b];
      return cur;
    }
    int mid = b + e >> 1;
    lc = build(b, mid, a);
    rc = build(mid + 1, e, a);
    pull(cur);
    return cur;
  }
  int upd(int pre, int b, int e, int i, int v) {
    int cur = ++T;
    t[cur] = t[pre];
    if (b == e) {
      t[cur].val = v; // += for adding 
      return cur;
    }
    int mid = b + e >> 1;
    if (i <= mid) lc = upd(t[pre].l, b, mid, i, v);
    else rc = upd(t[pre].r, mid + 1, e, i, v);
    pull(cur);
    return cur;
  }
  // Batch update: applies a sorted vector of updates {index, delta} in range [ql, qr]
  int upd_batch(int pre, int b, int e, const vector<pair<int, int>>& up, int ql, int qr) {
    if (ql > qr) return pre;
    int cur = ++T;
    t[cur] = t[pre];
    if (b == e) {
      for (int i = ql; i <= qr; ++i) t[cur].val += up[i].second;
      return cur;
    }
    int mid = b + e >> 1;
    int sp = upper_bound(up.begin() + ql, up.begin() + qr + 1, mid,
      [](int m, const pair<int, int>& p) { return m < p.first; }) - up.begin();
    lc = upd_batch(t[pre].l, b, mid, up, ql, sp - 1);
    rc = upd_batch(t[pre].r, mid + 1, e, up, sp, qr);
    pull(cur);
    return cur;
  }
  // Range query on a single version
  int query(int cur, int b, int e, int l, int r) {
    if (!cur || l > e || r < b) return 0; // Identity value (0 for sum, INF for min)
    if (l <= b && e <= r) return t[cur].val;
    int mid = b + e >> 1;
    return combine(query(lc, b, mid, l, r), query(rc, mid + 1, e, l, r));
  }
  // Query k-th smallest element between versions pre and cur
  int query_kth(int pre, int cur, int b, int e, int k) {
    if (b == e) return b;
    int cnt = t[lc].val - t[t[pre].l].val;
    int mid = b + e >> 1;
    if (cnt >= k) return query_kth(t[pre].l, lc, b, mid, k);
    else return query_kth(t[pre].r, rc, mid + 1, e, k - cnt);
  }
#undef lc
#undef rc
};