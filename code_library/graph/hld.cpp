VI heavy, chain, label, par, sz, dep;
int timer;
void dfsz(int u, int p, VVI& tree) {
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
void dfshld(int u, int p, VVI& tree, int head) {
  label[u] = timer++;
  chain[u] = head;
  if (heavy[u] != -1) dfshld(heavy[u], u, tree, head);
  for (int v : tree[u]) {
    if (v == p || v == heavy[u]) continue;
    dfshld(v, u, tree, v);
  }
}
void inithld(int n, VVI& tree) {
  heavy = VI(n + 1, -1);
  chain = VI(n + 1);
  label = VI(n + 1);
  sz = VI(n + 1);
  par = VI(n + 1);
  dep = VI(n + 1);
  timer = 1;
  dfsz(1, 0, tree);
  dfshld(1, 0, tree, 1);
}
ll query(int u, int v, fenwick& bit) {
  ll ret = 0;  // init value
  for (; chain[u] != chain[v]; v = par[chain[v]]) {
    if (dep[chain[u]] > dep[chain[v]]) swap(u, v);
    // ret ?= bit.rsq(label[chain[v]], label[v]);
  }
  if (dep[u] > dep[v]) swap(u, v);
  // lca = u
  // ret ?= bit.rsq(label[u], label[v]);
  return ret;
}