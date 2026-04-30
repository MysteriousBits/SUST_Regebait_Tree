struct LCA {
  int step = 0, k = 0;
  vector<int> vis_start, vis_end;
  vector<vector<int>> st;
  vector<vector<int>>& tree;
  LCA(vector<vector<int>>& tree) : tree(tree) { init(tree.size() - 1); }
  void build_st(int u, int p) {
    st[u][0] = p;
    for (int i = 1; i <= k; ++i) st[u][i] = st[st[u][i - 1]][i - 1];
  }
  void dfs(int u, int p) {
    vis_start[u] = step++;
    build_st(u, p);
    for (auto v : tree[u]) {
      if (v != p) dfs(v, u);
    }
    vis_end[u] = step++;
  }
  bool is_ancestor(int a, int b) {
    return vis_start[a] < vis_start[b] && vis_end[a] > vis_end[b];
  }
  int get(int a, int b) {
    if (a == b) return a;
    if (is_ancestor(a, b)) return a;
    if (is_ancestor(b, a)) return b;
    for (int i = k; i >= 0; --i) {
      if (!is_ancestor(st[a][i], b)) a = st[a][i];
    }
    return st[a][0];
  }
  void init(int n) {
    vis_start.assign(n + 1, 0);
    vis_end.assign(n + 1, 0);
    k = __lg(2 * n - 1);
    st.assign(n + 1, vector<int>(k + 1));
    dfs(1, 1);
  }
  // Extra
  int get_ancestor(int u, int n) {
    for (int i = 0; n > 0; ++i) {
      if (n & (1 << i)) {
        u = st[u][i];
        n -= (1 << i);
      }
    }
    return u;
  }
};