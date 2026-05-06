// 0-based index
template <typename T>
struct MST {
  int n;
  vector<vector<T>> tree;
  MST(vector<T>& a) : n(a.size()) {
    tree.resize(4 * n);
    build(0, 0, n - 1, a);
  }
  void build(int u, int l, int r, vector<T>& a) {
    if (l == r) {
      tree[u].pb(a[l]);
      return;
    }
    int mid = (l + r) / 2;
    build(2 * u + 1, l, mid, a);
    build(2 * u + 2, mid + 1, r, a);
    tree[u].resize(r - l + 1);
    merge(all(tree[2 * u + 1]), all(tree[2 * u + 2]), tree[u].begin());
  }
  // Returns number of elements smaller than x in range l, r
  int query(int l, int r, T x) { return get(0, 0, n - 1, l, r, x); }
  int get(int u, int tl, int tr, int l, int r, T x) {
    if (tl >= l && tr <= r)
      return lower_bound(all(tree[u]), x) - tree[u].begin();
    if (tl > r || tr < l) return 0;
    int mid = (tl + tr) / 2;
    return get(2 * u + 1, tl, mid, l, r, x) +
           get(2 * u + 2, mid + 1, tr, l, r, x);
  }
};
