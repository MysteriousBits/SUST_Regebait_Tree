VVI scc;
VI stk;
int disc[MAXN], low[MAXN];
bool instk[MAXN];
int cur_time;
void dfs_scc(int u, VVI& g) {
  disc[u] = low[u] = ++cur_time;
  instk[u] = true;
  stk.pb(u);
  for (int v : g[u]) {
    if (!disc[v]) {
      dfs_scc(v, g);
      low[u] = min(low[u], low[v]);
    } else if (instk[v])
      low[u] = min(low[u], disc[v]);
  }
  if (low[u] < disc[u]) return;
  scc.pb(VI());
  bool rem = true;
  while (rem) {
    int v = stk.back();
    stk.pop_back();
    instk[v] = false;
    scc.back().pb(v);
    rem = v != u;
  }
}
void tarjan(VVI& g) {
  cur_time = 0;
  int n = g.size();
  for (int i = 0; i < n; ++i) disc[i] = 0;
  for (int u = 1; u < n; ++u)
    if (!disc[u]) dfs_scc(u, g);
}
