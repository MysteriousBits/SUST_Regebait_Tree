
struct CD {
  vector<vector<int>>& tree;
  vector<int> par, sz;
  vector<bool> dead;
  CD(vector<vector<int>>& tree) : tree(tree) {
    par.resize(tree.size());
    sz.resize(tree.size());
    dead.resize(tree.size());
    build(1, 0);
  }
  void build(int u, int p) {
    dfs(u, p);
    u = dfs(u, p, sz[u]);
    dead[u] = true;
    par[u] = p;
    for (int v : tree[u]) {
      if (!dead[v]) build(v, u);
    }
  }
  void dfs(int u, int p) {
    sz[u] = 1;
    for (int v : tree[u]) {
      if (v == p || dead[v]) continue;
      dfs(v, u);
      sz[u] += sz[v];
    }
  }
  int dfs(int u, int p, int n) {
    for (int v : tree[u]) {
      if (v == p || dead[v]) continue;
      if (sz[v] > n / 2) return dfs(v, u, n);
    }
    return u;
  }
  int operator[](int i) { return par[i]; }
};