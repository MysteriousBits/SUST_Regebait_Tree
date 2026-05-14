
vector<vector<pii>> ed;  // ed[u] = {(v, edge_id), ...}
vector<int> num, isArt;
vector<pii> bridges;  // {u, v} for each bridge
vector<int> st;       // edge stack
int Time = 0;
template <class F>
int dfs(int at, int par, F& f) {
  int me = num[at] = ++Time;
  int top = me;
  int children = 0;
  for (auto [y, e] : ed[at]) {
    if (e == par) continue;
    if (num[y]) {
      top = min(top, num[y]);
      if (num[y] < me) st.push_back(e);  // back edge
    } else {
      children++;
      int si = sz(st);
      int up = dfs(y, e, f);
      top = min(top, up);
      if (par != -1 && up >= me) isArt[at] = 1;
      if (up > me) bridges.push_back({at, y});
      if (up >= me) {
        st.push_back(e);
        vi comp(st.begin() + si, st.end());
        f(comp);
        st.resize(si);
      } else {
        st.push_back(e);
      }
    }
  }
  if (par == -1 && children > 1) isArt[at] = 1;
  return top;
}
template <class F>
void bicomps(int n, F f) {
  ed.resize(n);
  num.assign(n, 0);
  isArt.assign(n, 0);
  bridges.clear();
  st.clear();
  Time = 0;
  rep(i, 0, n) if (!num[i]) dfs(i, -1, f);
}
// --- Shortened usage ---
int main() {
    int n, m; cin >> n >> m;
    ed.assign(n, {});
    rep(i, 0, m) {
        int u, v; cin >> u >> v;
        ed[u].push_back({v, i});
        ed[v].push_back({u, i});
    }
    // Callback receives a vector of edge IDs (from the input order)
    bicomps(n, [&](const vi& comp) {
        // Process BCC (e.g., store it, or iterate edges)
    });
}