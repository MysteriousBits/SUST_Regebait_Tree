template <typename T>  // 1 based index
struct ST {
#define lc (n << 1)
#define rc ((n << 1) | 1)
  vector<T> t, lazy;
  T identity = 0, lazy_identity = 0;  // 0 for sum, 1e18 for min etc
  ST(int n) { lazy.resize(4 * n, lazy_identity), t.resize(4 * n, identity); }
  inline void push(int n, int b, int e) {
    if (lazy[n] == lazy_identity) return;
    t[n] = t[n] + lazy[n] * (e - b + 1); // apply lazy
    if (b != e) {
      lazy[lc] = lazy[lc] + lazy[n];
      lazy[rc] = lazy[rc] + lazy[n];
    }
    lazy[n] = lazy_identity;
  }
  inline T combine(T a, T b) { return a + b; }
  inline void pull(int n) { t[n] = combine(t[lc], t[rc]); }
  void build(int n, int b, int e, vector<T>& a) {
    lazy[n] = lazy_identity;
    if (b == e) {
      t[n] = a[b];
      return;
    }
    int mid = (b + e) >> 1;
    build(lc, b, mid, a);
    build(rc, mid + 1, e, a);
    pull(n);
  }
  void upd(int n, int b, int e, int i, int j, T v) {
    push(n, b, e);
    if (j < b || e < i) return;
    if (i <= b && e <= j) {
      lazy[n] += v;  // set lazy
      push(n, b, e);
      return;
    }
    int mid = (b + e) >> 1;
    upd(lc, b, mid, i, j, v);
    upd(rc, mid + 1, e, i, j, v);
    pull(n);
  }
  T query(int n, int b, int e, int i, int j) {
    if (i > e || b > j) return identity;
    push(n, b, e);
    if (i <= b && e <= j) return t[n];
    int mid = (b + e) >> 1;
    return combine(query(lc, b, mid, i, j), query(rc, mid + 1, e, i, j));
  }
};