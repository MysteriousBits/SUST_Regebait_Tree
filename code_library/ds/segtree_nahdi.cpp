const int N = 5e5 + 9;
int a[N];

struct ST {
  #define lc (nd << 1)
  #define rc ((nd << 1) | 1)
  long long t[4 * N];

  ST() {
    memset(t, 0, sizeof t);
  }

  inline long long combine(long long a, long long b) {
    return a + b; // Change this for Max, Min, XOR, etc.
  }

  inline void pull(int nd) {
    t[nd] = combine(t[lc], t[rc]);
  }

  void build(int nd, int b, int e) {
    if (b == e) {
      t[nd] = a[b];
      return;
    }
    int mid = (b + e) >> 1;
    build(lc, b, mid);
    build(rc, mid + 1, e);
    pull(nd);
  }
  void upd(int nd, int b, int e, int i, long long v) {
    if (b == e) {
      t[nd] = v; // For "add v", use t[nd] += v;
      return;
    }
    int mid = (b + e) >> 1;
    if (i <= mid) upd(lc, b, mid, i, v);
    else upd(rc, mid + 1, e, i, v);
    pull(nd);
  }
  long long query(int nd, int b, int e, int i, int j) {
    if (i > e || b > j) return 0; // Return identity (0 for sum, 1e18 for min, etc.)
    if (i <= b && e <= j) return t[nd];
    int mid = (b + e) >> 1;
    return combine(query(lc, b, mid, i, j), query(rc, mid + 1, e, i, j));
  }
};