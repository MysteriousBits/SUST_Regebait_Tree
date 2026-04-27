
template <typename T>
struct segtree {
#define left(u) 2 * u + 1
#define right(u) 2 * u + 2
  int n;
  T init_val;
  vector<T> tree;
  function<T(T, T)> f;
  bool is_lazy = false;
  T init_lazy;
  vector<T> lazy;
  function<void(T&, T, int, int)> apply_lazy;
  function<void(T&, T)> merge_lazy;
  segtree() {}  // Dummy constructor for global declaration
  segtree(int sz, function<T(T, T)> f, T val = 0) {
    n = sz;
    this->f = f;
    init_val = val;
    tree.assign(1 << (__lg(n - 1) + 2), init_val);
  }
  // apply(tree[u], lazy[u], l, r)
  // merge(lazy[left(u)], lazy[u])
  void make_lazy(function<void(T&, T, int, int)> apply,
                 function<void(T&, T)> merge, T init = 0) {
    is_lazy = true;
    init_lazy = init;
    apply_lazy = apply;
    merge_lazy = merge;
    lazy.assign(tree.size(), init_lazy);
  }
  void build(vector<T>& a) { _build(0, 0, n - 1, a); }
  void update(int i, T x) { _update(0, 0, n - 1, i, x); }
  void update(int l, int r, T x) { _update_range(0, 0, n - 1, l, r, x); }
  T get(int l, int r) { return _get(0, 0, n - 1, l, r); }
  void _build(int u, int l, int r, vector<T>& a) {
    if (l == r) {
      tree[u] = a[l];
      return;
    }
    int mid = (l + r) / 2;
    _build(left(u), l, mid, a);
    _build(right(u), mid + 1, r, a);
    tree[u] = f(tree[left(u)], tree[right(u)]);
  }
  void _update(int u, int l, int r, int i, T x) {
    if (l == r) {
      tree[u] = x;
      return;
    }
    int mid = (l + r) / 2;
    if (i <= mid)
      _update(left(u), l, mid, i, x);
    else
      _update(right(u), mid + 1, r, i, x);
    tree[u] = f(tree[left(u)], tree[right(u)]);
  }
  void propagate(int u, int l, int r) {
    if (lazy[u] == init_lazy || l == r) return;
    int m = (l + r) / 2;
    apply_lazy(tree[left(u)], lazy[u], l, m);
    merge_lazy(lazy[left(u)], lazy[u]);
    apply_lazy(tree[right(u)], lazy[u], m + 1, r);
    merge_lazy(lazy[right(u)], lazy[u]);
    lazy[u] = init_lazy;
  }
  void _update_range(int u, int tl, int tr, int l, int r, T x) {
    if (l > tr || r < tl) return;
    if (tl >= l && tr <= r) {
      apply_lazy(tree[u], x, tl, tr);
      merge_lazy(lazy[u], x);
      return;
    }
    propagate(u, tl, tr);
    int mid = (tl + tr) / 2;
    _update_range(left(u), tl, mid, l, r, x);
    _update_range(right(u), mid + 1, tr, l, r, x);
    tree[u] = f(tree[left(u)], tree[right(u)]);
  }
  T _get(int u, int tl, int tr, int l, int r) {
    if (l > tr || r < tl) return init_val;
    if (l <= tl && r >= tr) return tree[u];
    if (is_lazy) propagate(u, tl, tr);
    int mid = (tl + tr) / 2;
    return f(_get(left(u), tl, mid, l, r), _get(right(u), mid + 1, tr, l, r));
  }
#undef left
#undef right
};