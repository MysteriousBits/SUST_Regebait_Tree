
struct dsu {
  vector<int> parent, size;
  dsu(int n) {
    parent.resize(n + 1);
    size.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
      parent[i] = i;
      size[i] = 1;
    }
  }
  int find(int u) {
    if (parent[u] == u) return u;
    return parent[u] = find(parent[u]);
  }
  void merge(int u, int v) {
    u = find(u);
    v = find(v);
    if (u != v) {
      if (size[u] < size[v]) swap(u, v);
      parent[v] = u;
      size[u] += size[v];
    }
  }
};