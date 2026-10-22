struct HopcroftKarp {
  int n, m;
  vector<vector<int>> g;
  vector<int> l, r, d, q;

  HopcroftKarp(int n, int m) : n(n), m(m) {
    int p = n + m + 1; q.resize(n + 1, 0);
    g.resize(p); l.resize(p, 0); r.resize(p, 0); d.resize(n + 1, 0);
  }
  // 1 based offset n
  void add_edge(int u, int v) { g[u].push_back(v + n); }

  // Total matching size
  int solve() {
    int res = 0;
    auto dfs = [&](auto f, int u) -> bool {
      int t = exchange(d[u], 0) + 1;
      for (int v : g[u]) {
        if (r[v] == 0 || (d[r[v]] == t && f(f, r[v])))
          return l[u] = v, r[v] = u, 1;
      }
      return 0;
    };
    for (int t = 0, f = 0;; t = f = 0, fill(d.begin(), d.end(), 0)) {
      for (int i = 1; i <= n; ++i) if (l[i] == 0) q[t++] = i, d[i] = 1;
      for (int i = 0; i < t; ++i) for (int v : g[q[i]]) {
        if (r[v] == 0) f = 1;
        else if (!d[r[v]]) d[r[v]] = d[q[i]] + 1, q[t++] = r[v];
      }
      if (!f) return res;
      for (int i = 1; i <= n; ++i) if (l[i] == 0) res += dfs(dfs, i);
    }
  }
  // All matched pairs {a,b}
  vector<pair<int, int>> get_pairs() {
    vector<pair<int, int>> pairs;
    for (int u = 1; u <= n; ++u) {
      if (l[u] != 0) {
        pairs.push_back({u, l[u] - n});
      }
    }
    return pairs;
  }
};