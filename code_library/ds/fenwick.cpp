struct fenwick {
  int n;
  vector<ll> tree;
  fenwick(int s) {
    n = s;
    tree.assign(n + 1, 0);
  }
  ll get(int i) {
    ll res = 0;
    for (; i > 0; i -= i & -i) res += tree[i];
    return res;
  }
  void add(int i, ll x) {
    for (; i <= n; i += i & -i) tree[i] += x;
  }
  void add(int l, int r, ll x) {
    add(l, x);
    if (r < n) add(r + 1, -x);
  }
  ll get(int l, int r) { return get(r) - get(l - 1); }
};