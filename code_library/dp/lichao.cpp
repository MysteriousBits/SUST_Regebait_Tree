struct LiChao {
  struct Line { ll m, c; ll f(ll x) { return m * x + c; } };
  vector<Line> tree;
  LiChao(int n) { tree.resize(4 * (n + 1), {0, INFL}); } // {0,-INFL} for max
  ll mp(int x) { return x; } // change: coordinate transform (monotonic)
  void add(int u, int l, int r, Line line) {
    int mid = (l + r) >> 1;
    if (line.f(mp(mid)) < tree[u].f(mp(mid))) swap(tree[u], line);
    if (l == r) return;
    if (line.f(mp(l)) < tree[u].f(mp(l))) add(u<<1, l, mid, line);
    else add((u<<1)|1, mid + 1, r, line);
  }
  ll query(int u, int l, int r, int x) {
    ll ans = tree[u].f(mp(x));
    if (l == r) return ans;
    int mid = (l + r) >> 1;
    if (x <= mid) return min(ans, query(u<<1, l, mid, x));
    else return min(ans, query((u<<1)|1, mid + 1, r, x));
  }
};