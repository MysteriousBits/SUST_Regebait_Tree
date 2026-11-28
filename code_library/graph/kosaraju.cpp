class Kosaraju{
  public:
  int n;
  vector<vector<int32_t>> g, rg;
  vector<int32_t> comp,order,sz; vector<bool> vis;
  void dfs1(int u) {
    vis[u] = true;
    for (int v : g[u]) {
      if(!vis[v]) dfs1(v);
    }
    order.push_back(u);
  }
  void dfs2(int u, int c) {
    comp[u] = c; sz[comp[u]]++;
    for (auto& v : rg[u]) {
      if(comp[v] == -1) dfs2(v, c);
    }
  }
  Kosaraju(int n) : n(n) {
    g.assign(n + 1, {});
    rg.assign(n + 1, {});
    sz.assign(n + 1, 0);
  }
  inline void add_edge(int u, int v) {
    g[u].push_back(v);
    rg[v].push_back(u);
  }
  int build() {
    vis.assign(n + 1, false);
    order.clear();
    for (int i = 1; i <= n; i++) {
      if (!vis[i]) dfs1(i);
    }
    comp.assign(n + 1, -1);
    reverse(order.begin(), order.end());
    int scc = 0;
    for (int u : order) {
      if (comp[u] == -1) {
        dfs2(u, ++scc); 
      }
    }
    return scc;
  }
  vector<vector<int32_t>> build_dag(int scc) {
    vector<vector<int32_t>> dag(scc + 1);
    for (int u = 1; u <= n; u++) {
      for (int v : g[u]) {
        if (comp[u] != comp[v]){
          dag[comp[u]].push_back(comp[v]);
        }
      }
    }
    return dag;
  }
};