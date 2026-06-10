// g[u] = {{neighbor, edge_id}, ...}
vector<vector<pair<int,int>>> g;
vector<int> tin, low, st;
vector<bool> is_art;
vector<vector<int>> bccs;
int timer;
void dfs(int u, int pe) {
  tin[u] = low[u] = ++timer;
  int ch = 0;
  for (auto [v, id] : g[u]) {
    if (id == pe) continue;
    if (tin[v]) {
      low[u] = min(low[u], tin[v]);
      if (tin[v] < tin[u]) st.push_back(id);
    } else {
      ch++;
      st.push_back(id);
      dfs(v, id);
      low[u] = min(low[u], low[v]);
      if (low[v] >= tin[u]) {
        if (pe != -1) is_art[u] = true;
        bccs.emplace_back();
        do {
          bccs.back().push_back(st.back());
          st.pop_back();
        } while (bccs.back().back() != id);
      }
    }
  }
  if (pe == -1 && ch > 1) is_art[u] = true;
}
void get_bcc(int n) {
  tin.assign(n + 1, 0); low.assign(n + 1, 0);
  is_art.assign(n + 1, false);
  st.clear(); bccs.clear(); timer = 0;
  for (int i = 1; i <= n; i++) {
    if (!tin[i]) {
      dfs(i, -1);
      if (!st.empty()) {
        bccs.push_back(st);
        st.clear();
      }
    }
  }
}