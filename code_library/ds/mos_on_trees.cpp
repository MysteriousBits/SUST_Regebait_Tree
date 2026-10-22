int mot = 0;
int euler[2 * MAXN], moin[MAXN], mout[MAXN];
bool inpt[MAXN];

void dfs_mo(int u, int p, vector<vector<int>>& adj) {
  moin[u] = ++mot; euler[mot] = u;
  for (int v : adj[u]) if (v != p) dfs_mo(v, u, adj);
  mout[u] = ++mot; euler[mot] = u;
}
void add(int node) { /* ... */ }
void del(int node) { /* ... */ }
int calc() { /* ... */ }

void toggle(int node) {
  if (inpt[node]) del(node);
  else add(node);
  inpt[node] ^= 1;
}

struct Query { int l, r, lca, id; };
vector<int> mo_tree(vector<pair<int, int>>& qs, LCA& lca) {
  int blk = max(1, (int)sqrt(mot)); 
  vector<Query> Q;
  for (int i = 0; i < qs.size(); i++) {
    int u = qs[i].first; int v = qs[i].second;
    if (moin[u] > moin[v]) swap(u, v);
    
    int lc = lca.get(u, v); 
    if (lc == u) Q.push_back({moin[u], moin[v], -1, i}); // case 1
    else Q.push_back({mout[u], moin[v], lc, i}); // Case 2
  }
  vector<int> s(Q.size()), res(Q.size());
  iota(s.begin(), s.end(), 0);

  sort(s.begin(), s.end(), [&](int i, int j) {
    int bi = Q[i].l / blk;
    int bj = Q[j].l / blk;
    if (bi != bj) return bi < bj;
    if (bi & 1) return Q[i].r < Q[j].r;
    return Q[i].r > Q[j].r;
  });

  int L = 1, R = 0;
  for (int qi : s) {
    Query q = Q[qi];
    int ql = q.l;
    int qr = q.r;
    
    while (L > ql) { --L; toggle(euler[L]); }
    while (R < qr) { ++R; toggle(euler[R]); }
    while (L < ql) { toggle(euler[L]); L++; }
    while (R > qr) { toggle(euler[R]); R--; }
    
    if (q.lca != -1) toggle(q.lca); // case 2
    res[q.id] = calc();
    if (q.lca != -1) toggle(q.lca); // case 2
  }
  return res;
}