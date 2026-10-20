struct PST {
#define lc t[cur].l
#define rc t[cur].r
  struct node {
    int l = 0, r = 0;
    ll val = 0, lazy = 0;
  } t[250 * N];
  int T = 0;
  
  inline ll combine(ll a, ll b) {
    return a + b;
  }
  inline void pull(int cur) {
    t[cur].val = combine(t[lc].val, t[rc].val);
  }
  int build(int b, int e) {
    int cur = ++T;
    if(b == e) return cur;
    int mid = b + e >> 1;
    lc = build(b, mid);
    rc = build(mid + 1, e);
    pull(cur);
    return cur;
  }
  void apply(int cur, int b, int e, ll v) {
    t[cur].lazy += v;
    t[cur].val += (ll)(e - b + 1) * v;
  }
  void push(int cur, int b, int e) {
    if(!t[cur].lazy) return;
    if(b != e) {
      int mid = b + e >> 1;

      int nlc = ++T; t[nlc] = t[lc];
      int nrc = ++T; t[nrc] = t[rc];
      lc = nlc; rc = nrc;

      apply(lc, b, mid, t[cur].lazy);
      apply(rc, mid + 1, e, t[cur].lazy);
    }
    t[cur].lazy = 0;
  }
  int upd(int pre, int b, int e, int i, int j, ll v) {
    int cur = ++T;
    t[cur] = t[pre];
    if(i <= b && e <= j) {
      apply(cur, b, e, v);
      return cur;
    }
    push(cur, b, e);
    int mid = b + e >> 1;
    if(i <= mid) lc = upd(lc, b, mid, i, j, v);
    if(j > mid) rc = upd(rc, mid + 1, e, i, j, v);
    pull(cur);
    return cur;
  }
  // Propagating query
  ll query(int cur, int b, int e, int i, int j) {
    if(!cur || b > j || e < i) return 0;
    if(i <= b && e <= j) return t[cur].val;
    push(cur, b, e);
    int mid = b + e >> 1;
    return combine(query(lc, b, mid, i, j), query(rc, mid + 1, e, i, j));
  }
  // Non-propagating query
  ll query(int cur, int b, int e, int i, int j, ll add = 0) {
    if(!cur || b > j || e < i) return 0;
    if(i <= b && e <= j) return t[cur].val + (ll)(e - b + 1) * add;
    int mid = (b + e) >> 1;
    add += t[cur].lazy;
    return combine(query(lc, b, mid, i, j, add), query(rc, mid + 1, e, i, j, add));
  }
#undef lc
#undef rc 
};