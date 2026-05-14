int hopcroftKarp(vector<vi>& g, vi& r) {
  int n = sz(g), res = 0;
  vi l(n, -1), q(n), d(n);
  auto dfs = [&](auto f, int u) -> bool {
    int t = exchange(d[u], 0) + 1;
    for (int v : g[u])
      if (r[v] == -1 || (d[r[v]] == t && f(f, r[v])))
        return l[u] = v, r[v] = u, 1;
    return 0;
  };
  for (int t = 0, f = 0;; t = f = 0, d.assign(n, 0)) {
    rep(i, 0, n) if (l[i] == -1) q[t++] = i, d[i] = 1;
    rep(i, 0, t) for (int v : g[q[i]]) {
      if (r[v] == -1)
        f = 1;
      else if (!d[r[v]])
        d[r[v]] = d[q[i]] + 1, q[t++] = r[v];
    }
    if (!f) return res;
    rep(i, 0, n) if (l[i] == -1) res += dfs(dfs, i);
  }
}
// --- Shortened usage ---
int main() {
    int n, m, k; cin >> n >> m >> k;
    vi r(n + m, -1); vector<vi> g(n + m);
    rep(i, 0, k) {
        int u, v; cin >> u >> v;
        g[u-1].push_back(v + n - 1); // Map right side to [n, n+m)
    }
    int matchingSize = hopcroftKarp(g, r);
    // r[i] stores the left-side match for right-side node i
    for (int i = n; i < n + m; i++)
        if (r[i] != -1) cout << r[i] + 1 << " " << i - n + 1 << endl;
}