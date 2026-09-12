int hopcroft(int n, int m, vector<vector<int>>& g, vector<int>& l) {
  vector<int> r(m + 1), d(n + 1), ptr(n + 1);
  auto dfs = [&](auto&& f, int u) -> bool {
    if (!u) return true;
    for (int& p = ptr[u]; p < (int)g[u].size(); ++p) {
      int v = g[u][p];
      if (d[r[v]] == d[u] + 1 && f(f, r[v]))
        return l[u] = v, r[v] = u, true;
    }
    return false;
  };
  int match = 0;
  while (true) {
    d.assign(n + 1, n + 2);
    queue<int> q;
    for (int u = 1; u <= n; ++u)
      if (!l[u]) q.push(u), d[u] = 0;
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int v : g[u]) {
        if (d[r[v]] != n + 2) continue;
        if (r[v]) q.push(r[v]);
        d[r[v]] = d[u] + 1;
      }
    }
    if (d[0] == n + 2) return match;
    ptr.assign(n + 1, 0);
    for (int u = 1; u <= n; ++u)
      if (!l[u]) match += dfs(dfs, u);
  }
}