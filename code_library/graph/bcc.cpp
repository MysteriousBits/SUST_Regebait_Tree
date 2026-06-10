// g[u] = {{neighbor, edge_id}, ...}
vector<vector<pair<int,int>>> g;
vector<int> tin, st, bridges;
vector<bool> is_art;
vector<vector<int>> bccs;
int timer;
int dfs(int u, int pe) {
  int me = tin[u] = ++timer, top = me, ch = 0;
  for (auto [v, id] : g[u]) if (id != pe) {
    if (tin[v]) {
      top = min(top, tin[v]);
      if (tin[v] < me) st.push_back(id);
    } else {
      ch++;
      int si = st.size();
      int up = dfs(v, id);
      top = min(top, up);
      if (up >= me) {
        if (pe != -1) is_art[u] = true;
        if (up == me) {
          st.push_back(id);
          bccs.push_back({st.begin() + si, st.end()});
          st.resize(si);
        } else {
          bridges.push_back(id);
        }
      } else {
        st.push_back(id);
      }
    }
  }
  if (pe == -1 && ch > 1) is_art[u] = true;
  return top;
}
void get_bcc(int n) {
  tin.assign(n + 1, 0); is_art.assign(n + 1, false);
  st.clear(); bccs.clear(); bridges.clear(); timer = 0;
  for (int i = 1; i <= n; i++) if (!tin[i]) dfs(i, -1);
}