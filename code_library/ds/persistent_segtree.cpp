template <typename T>
struct PST {
  struct node {
    T val;
    int l, r;
  };
  int n;
  T identity = 0;  // 0 for sum, INF for min etc
  vector<node> nodes;
  vector<int> version;
  T merge(T x, T y) { return x + y; }
  PST() {}
  PST(int sz) {
    n = sz;
    build(vector<T>(n, identity));
  }
  PST(vector<T>& a) {
    n = a.size();
    build(a);
  }
  int build(const vector<T>& a) {
    nodes.reserve(20 * n);
    int root = _build(0, n - 1, a);
    version.push_back(root);
    return version.size() - 1;
  }
  int _build(int l, int r, const vector<T>& a) {
    int root = nodes.size();
    nodes.push_back({});
    if (l == r) {
      nodes[root].val = a[l];
      return root;
    }
    int mid = (l + r) / 2;
    int ch = _build(l, mid, a);
    nodes[root].l = ch;
    ch = _build(mid + 1, r, a);
    nodes[root].r = ch;
    nodes[root].val = merge(nodes[nodes[root].l].val, nodes[nodes[root].r].val);
    return root;
  }
  int update(int i, T x, int v = -1) {
    if (v == -1) v = version.size() - 1;
    int root = _update(version[v], 0, n - 1, i, x);
    version.push_back(root);
    return version.size() - 1;
  }
  int _update(int u, int l, int r, int i, T x) {
    int root = nodes.size();
    node old = nodes[u];
    nodes.push_back(old);
    if (l == r) {
      nodes[root].val = x;  // change = to += for add
      return root;
    }
    int mid = (l + r) / 2;
    if (i <= mid) {
      int ch = _update(nodes[u].l, l, mid, i, x);
      nodes[root].l = ch;
    } else {
      int ch = _update(nodes[u].r, mid + 1, r, i, x);
      nodes[root].r = ch;
    }
    nodes[root].val = merge(nodes[nodes[root].l].val, nodes[nodes[root].r].val);
    return root;
  }
  T get(int l, int r, int v) { return _get(version[v], 0, n - 1, l, r); }
  T _get(int u, int tl, int tr, int l, int r) {
    if (l > tr || r < tl) return identity;
    if (l <= tl && r >= tr) return nodes[u].val;
    int mid = (tl + tr) / 2;
    return merge(_get(nodes[u].l, tl, mid, l, r),
      _get(nodes[u].r, mid + 1, tr, l, r));
  }
  // version is 1 indexed (0 is the initial before updates)
  T get_kth(int ver_l, int ver_r, int k) {
    return _get_kth(version[ver_l - 1], version[ver_r], 0, n - 1, k);
  }
  int _get_kth(int u, int v, int l, int r, int k) {
    if (l == r) return l;
    int mid = (l + r) / 2;
    T kl = nodes[nodes[v].l].val - nodes[nodes[u].l].val;
    if (kl >= k)
      return _get_kth(nodes[u].l, nodes[v].l, l, mid, k);
    else
      return _get_kth(nodes[u].r, nodes[v].r, mid + 1, r, k - kl);
  }
};