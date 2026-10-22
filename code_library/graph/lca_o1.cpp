struct LCA {
  vector<int> hit, tin, tout; // hit[u] height
  vector<vector<int>>& adj;
  SparseTable<pair<int, int>> st; // pair<depth, node_id>
  int timer;

  LCA(vector<vector<int>>& adj, int root = 1) : adj(adj) {
    int n = adj.size();
    hit.assign(n, 0); tin.assign(n, 0); tout.assign(n, 0);
    st.a.resize(2 * n + 5); timer = 0;
    dfs(root, 0, 0); st.build(timer);
  }
  void dfs(int u, int p, int d) {
    hit[u] = d, tin[u] = ++timer;
    st.a[timer] = {hit[u], u};

    for (int v : adj[u]) {
      if (v != p) { dfs(v, u, d + 1); st.a[++timer] = {hit[u], u}; }
    }
    tout[u] = timer;
  }
  int get(int u, int v) {
    int l = tin[u], r = tin[v]; if (l > r) swap(l, r);
    return st.query(l, r).second; // min in interval [l,r]
  }
  int dist(int u, int v) {
    return hit[u] + hit[v] - 2 * hit[get(u, v)];
  }
};