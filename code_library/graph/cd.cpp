
struct CD {
  vector<set<int>> tree;
  vector<int> par, sz;
  CD(vector<vector<int>>& tree) {
    for (auto& v : tree) {
      this->tree.emplace_back(v.begin(), v.end());
    }
    par.resize(tree.size());
    sz.resize(tree.size());
    build(1, 0);
  }
  void build(int u, int p) {
    dfs(u, p);
    int centroid = dfs(u, p, sz[u]);
    par[centroid] = p;
    vector<int> adj(tree[centroid].begin(), tree[centroid].end());
    for (int v : adj) {
      tree[v].erase(centroid);
      tree[centroid].erase(v);
      build(v, centroid);
    }
  }
  void dfs(int u, int p) {
    sz[u] = 1;
    for (int v : tree[u]) {
      if (v == p) continue;
      dfs(v, u);
      sz[u] += sz[v];
    }
  }
  int dfs(int u, int p, int n) {
    for (int v : tree[u]) {
      if (v == p) continue;
      if (sz[v] > n / 2) return dfs(v, u, n);
    }
    return u;
  }
  int operator[](int i) { return par[i]; }
};