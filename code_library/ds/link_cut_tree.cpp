#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

struct node {
  int p = 0, c[2] = {0, 0}, sz = 0, ssz = 0, vsz = 0, mn_id = 0;
  bool flip = false;
  long long val = INF, sum = 0, lazy = 0, subsum = 0, vsum = 0, mn = INF;
  node() {}
  node(int id, long long x) : val(x), sum(x), subsum(x), mn(x), mn_id(id), sz(1), ssz(1) {}
};
struct LCT {
  vector<node> t;

  LCT(int n, int m = 0) : t(n + m + 1) {
    for (int i = 1; i <= n + m; i++) t[i] = node(i, INF);
    t[0] = node();
    t[0].sz = t[0].ssz = t[0].vsz = t[0].sum = t[0].subsum = t[0].vsum = 0;
  }
  bool is_root(int x) { return t[t[x].p].c[0] != x && t[t[x].p].c[1] != x; }
  int dir(int x) { return t[t[x].p].c[1] == x; }
  void flip(int x) {
    if (x) swap(t[x].c[0], t[x].c[1]), t[x].flip ^= 1;
  }
  void add(int x, long long v) {
    if (!x) return;
    t[x].val += v; t[x].mn += v; t[x].lazy += v;
    t[x].sum += v * t[x].sz; t[x].subsum += v * t[x].ssz; t[x].vsum += v * t[x].vsz;
  }
  void push(int x) {
    if (!x) return;
    if (t[x].flip) flip(t[x].c[0]), flip(t[x].c[1]), t[x].flip = false;
    if (t[x].lazy) add(t[x].c[0], t[x].lazy), add(t[x].c[1], t[x].lazy), t[x].lazy = 0;
  }
  void pull(int x) {
    if (!x) return;
    int l = t[x].c[0], r = t[x].c[1];
    t[x].sz = t[l].sz + t[r].sz + 1;
    t[x].ssz = t[l].ssz + t[r].ssz + t[x].vsz + 1;
    t[x].sum = t[l].sum + t[r].sum + t[x].val;
    t[x].subsum = t[l].subsum + t[r].subsum + t[x].vsum + t[x].val;
    t[x].mn = t[x].val; t[x].mn_id = x;
    if (t[l].mn < t[x].mn) t[x].mn = t[l].mn, t[x].mn_id = t[l].mn_id;
    if (t[r].mn < t[x].mn) t[x].mn = t[r].mn, t[x].mn_id = t[r].mn_id;
  }
  void push_all(int x) {
    if (!is_root(x)) push_all(t[x].p);
    push(x);
  }
  void rotate(int x) {
    int y = t[x].p, z = t[y].p, dx = dir(x), dy = dir(y), w = t[x].c[!dx];
    if (!is_root(y)) t[z].c[dy] = x;
    t[x].p = z; t[x].c[!dx] = y; t[y].p = x; t[y].c[dx] = w;
    if (w) t[w].p = y;
    pull(y); pull(x);
  }
  void splay(int x) {
    push_all(x);
    while (!is_root(x)) {
      int y = t[x].p;
      if (!is_root(y)) rotate(dir(x) == dir(y) ? y : x);
      rotate(x);
    }
  }
  int access(int u) {
    int last = 0;
    for (int v = 0; u; v = u, u = t[u].p) {
      splay(u);
      int r = t[u].c[1];
      t[u].vsz += t[r].ssz - t[v].ssz;
      t[u].vsum += t[r].subsum - t[v].subsum;
      t[u].c[1] = v; pull(u); last = u;
    }
    return last;
  }
  void make_root(int u) { access(u); splay(u); flip(u); }
  int find_root(int u) {
    access(u); splay(u); push(u);
    while (t[u].c[0]) u = t[u].c[0], push(u);
    splay(u);
    return u;
  }
  bool connected(int u, int v) { return find_root(u) == find_root(v); }
  void link(int u, int v) {
    make_root(u);
    if (find_root(v) == u) return;
    access(v); splay(v);
    t[u].p = v; t[v].vsz += t[u].ssz; t[v].vsum += t[u].subsum; pull(v);
  }
  void cut(int u, int v) {
    make_root(u); access(v); splay(v);
    if (t[v].c[0] == u && !t[u].c[1]) t[v].c[0] = t[u].p = 0, pull(v);
  }
  // --- Operations ---
  void link_edge(int e, int u, int v, long long w) { set_val(e, w); link(u, e); link(e, v); }
  void cut_edge(int e, int u, int v) { cut(u, e); cut(e, v); }
  void set_val(int u, long long x) { access(u); splay(u); t[u].val = x; pull(u); }
  void add_val(int u, long long x) { access(u); splay(u); t[u].val += x; pull(u); }
  void add_path(int u, int v, long long x) { make_root(u); access(v); splay(v); add(v, x); }
  pair<long long, int> query_min(int u, int v) { make_root(u); access(v); splay(v); return {t[v].mn, t[v].mn_id}; }
  long long query_path_sum(int u, int v) { make_root(u); access(v); splay(v); return t[v].sum; }
  long long query_subtree_sum(int u, int root = 1) { make_root(root); access(u); splay(u); return t[u].val + t[u].vsum; }
};