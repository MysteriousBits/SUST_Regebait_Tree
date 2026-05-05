template<typename T>
struct SparseTable {
  const int N = 1e5 + 9;
  vector<vector<T>> t;
  vector<T> a;

  T combine(T x, T y) { return min(x, y); }

  void build(int n) {
    t.assign(n + 1, vector<T>(18));
    for(int i = 1; i <= n; ++i) t[i][0] = a[i];
    for(int k = 1; k < 18; ++k)
      for(int i = 1; i + (1 << k) - 1 <= n; ++i)
        t[i][k] = combine(t[i][k-1], t[i + (1 << (k-1))][k-1]);
  }

  T query(int l, int r) {
    int k = 31 - __builtin_clz(r - l + 1);
    return combine(t[l][k], t[r - (1 << k) + 1][k]);
  }
};
