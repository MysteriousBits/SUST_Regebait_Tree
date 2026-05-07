vector<int> heavy, chain, label, par, sz, dep;
int timer;
void dfsz(int u, int p, vector<vector<int>>& tree) {
  sz[u] = 1;
  par[u] = p;
  dep[u] = dep[p] + 1;
  int mx = -1;
  for (int v : tree[u]) {
    if (v == p) continue;
    dfsz(v, u, tree);
    sz[u] += sz[v];
    if (sz[v] > mx) mx = sz[v], heavy[u] = v;
  }
}
void dfshld(int u, int p, vector<vector<int>>& tree, int head) {
  label[u] = timer++;
  chain[u] = head;
  if (heavy[u] != -1) dfshld(heavy[u], u, tree, head);
  for (int v : tree[u]) {
    if (v == p || v == heavy[u]) continue;
    dfshld(v, u, tree, v);
  }
}
void inithld(vector<vector<int>>& tree) {
  int n = tree.size();
  heavy = vector<int>(n, -1);
  chain = vector<int>(n);
  label = vector<int>(n);
  sz = vector<int>(n);
  par = vector<int>(n);
  dep = vector<int>(n);
  timer = 1;
  dfsz(1, 0, tree);
  dfshld(1, 0, tree, 1);
}
ll query(int u, int v /*, fenwick/segtree/anything& ds*/) {
  ll ret = 0;  // init value
  for (; chain[u] != chain[v]; v = par[chain[v]]) {
    if (dep[chain[u]] > dep[chain[v]]) swap(u, v);
    // ret ?= ds.query(label[chain[v]], label[v]);
  }
  if (dep[u] > dep[v]) swap(u, v);
  // lca is u
  // ret ?= ds.query(label[u], label[v]);
  return ret;
}
// Updating u : ds.update(label[u]...)