struct LCA {
  int t = 0, k = 0;
  vector<int> tin, tout;
  vector<vector<int>> st;
  vector<vector<int>>& tree;
  LCA(vector<vector<int>>& tree) : tree(tree) {
    int n = tree.size();
    tin.assign(n, 0); tout.assign(n, 0);
    k = __lg(2 * n - 1);
    st.assign(n, vector<int>(k + 1));
    dfs(1, 1);
  }
  void dfs(int u, int p) {
    tin[u] = t++; st[u][0] = p;
    for (int i = 1; i <= k; i++) st[u][i] = st[st[u][i-1]][i-1];
    for (auto v : tree[u]) if (v != p) dfs(v, u);
    tout[u] = t++;
  }
  bool is_anc(int a, int b) { return tin[a] < tin[b] && tout[a] > tout[b]; }
  int get(int a, int b) {
    if (a == b) return a;
    if (is_anc(a, b)) return a;
    if (is_anc(b, a)) return b;
    for (int i = k; i >= 0; i--) if (!is_anc(st[a][i], b)) a = st[a][i];
    return st[a][0];
  }
  int get_anc(int u, int n) { // n-th ancestor
    for (int i = 0; n > 0; i++)
      if (n & (1 << i)) u = st[u][i], n ^= (1 << i);
    return u;
  }
};