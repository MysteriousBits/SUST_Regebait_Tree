struct ST {
  #define lc (n << 1)
  #define rc ((n << 1) | 1)
  vector<ll> a, t, lazy;
  ST(vector<ll>& a) : a(a) {
    lazy.resize(4 * a.size() + 1, 0);
    t.resize(4 * a.size() + 1, 0);
  }
  ST(int n) {
    a.resize(n);
    lazy.resize(4 * n, 0);
    t.resize(4 * n, 0);
  }
  inline long long combine(long long a, long long b) {
    return (a + b) % mod;
  }
  inline void pull(int n) {
    t[n] = (t[lc] + t[rc]) % mod;
  }
  // Updates n and lazy directly
  inline void apply(int n, int b, int e, long long v) {
    v %= mod;
    lazy[n] = (lazy[n] + v) % mod;
    t[n] = (t[n] + (ll)(e - b + 1) * v) % mod;
  }
  inline void push(int n, int b, int e) {
    if (lazy[n] == 0) return;
    if (b != e) {
      int mid = (b + e) >> 1;
      apply(lc, b, mid, lazy[n]);
      apply(rc, mid + 1, e, lazy[n]);
    }
    lazy[n] = 0;
  }
  void build(int n, int b, int e) {
    lazy[n] = 0;
    if (b == e) {
      t[n] = a[b] % mod;
      return;
    }
    int mid = (b + e) >> 1;
    build(lc, b, mid);
    build(rc, mid + 1, e);
    pull(n);
  }
  void upd(int n, int b, int e, int i, int j, long long v) {
    if (j < b || e < i) return;
    if (i <= b && e <= j) {
      apply(n, b, e, v);
      return;
    }
    push(n, b, e);
    int mid = (b + e) >> 1;
    upd(lc, b, mid, i, j, v);
    upd(rc, mid + 1, e, i, j, v);
    pull(n);
  }
  long long query(int n, int b, int e, int i, int j) {
    if (i > e || b > j) return 0;
    if (i <= b && e <= j) return t[n];
    push(n, b, e);
    int mid = (b + e) >> 1;
    return combine(query(lc, b, mid, i, j), query(rc, mid + 1, e, i, j));
  }
};