template <typename T>  // 1 based
struct ST {
#define lc (nd << 1)
#define rc ((nd << 1) | 1)
  vector<T> t;
  T identity = 0;  // 0 for sum, 1e18 for min etc;
  ST(int n) { t.resize(4 * n, identity); }
  inline T combine(T a, T b) { return a + b; }
  inline void pull(int nd) { t[nd] = combine(t[lc], t[rc]); }
  void build(int nd, int b, int e, vector<T>& a) {
    if (b == e) {
      t[nd] = a[b];
      return;
    }
    int mid = (b + e) >> 1;
    build(lc, b, mid, a);
    build(rc, mid + 1, e, a);
    pull(nd);
  }
  void upd(int nd, int b, int e, int i, T v) {
    if (b == e) {
      t[nd] = v;  // For "add v", use t[nd] += v;
      return;
    }
    int mid = (b + e) >> 1;
    if (i <= mid) upd(lc, b, mid, i, v);
    else upd(rc, mid + 1, e, i, v);
    pull(nd);
  }
  T query(int nd, int b, int e, int i, int j) {
    if (i > e || b > j) return identity;
    if (i <= b && e <= j) return t[nd];
    int mid = (b + e) >> 1;
    return combine(query(lc, b, mid, i, j), query(rc, mid + 1, e, i, j));
  }
};