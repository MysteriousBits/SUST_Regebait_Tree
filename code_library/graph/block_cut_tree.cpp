int T, low[N], dis[N], art[N], sz;
vector<int> g[N], bcc[N], st;

void dfs(int u, int pre = 0) {
  low[u] = dis[u] = ++T;
  st.push_back(u);
  for (auto v : g[u]) {
    if (!dis[v]) {
      dfs(v, u);
      low[u] = min(low[u], low[v]);
      if (low[v] >= dis[u]) {
        sz++; int x;
        do { x = st.back(); st.pop_back(); bcc[x].push_back(sz); } while (x ^ v);
        bcc[u].push_back(sz);
      }
    } else if (v != pre) low[u] = min(low[u], dis[v]);
  }
}

int dep[N], par[N][20], cnt[N], id[N];
vector<int> bt[N];
void dfs1(int u, int pre = 0) {
  dep[u] = dep[pre] + 1; cnt[u] = cnt[pre] + art[u]; par[u][0] = pre;
  for (int k = 1; k <= 18; k++) par[u][k] = par[par[u][k - 1]][k - 1];
  for (auto v : bt[u]) if (v != pre) dfs1(v, u);
}
int lca(int u, int v) {
  if (dep[u] < dep[v]) swap(u, v);
  for (int k = 18; k >= 0; k--) if (dep[par[u][k]] >= dep[v]) u = par[u][k];
  if (u == v) return u;
  for (int k = 18; k >= 0; k--) if (par[u][k] != par[v][k]) u = par[u][k], v = par[v][k];
  return par[u][0];
}
int dist(int u, int v) {
  int lc = lca(u, v);
  return cnt[u] + cnt[v] - 2 * cnt[lc] + art[lc];
}