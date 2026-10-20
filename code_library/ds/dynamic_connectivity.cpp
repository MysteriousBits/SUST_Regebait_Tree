struct ST {
#define lc (n << 1)
#define rc ((n << 1) | 1)
  vector<query> t[maxN*4];
  ST(int n) {}
  void upd(int n, int b, int e, int ql, int qr, query& v) {
    if(ql <= b && e <= qr) {
        t[n].push_back(v);
        return;
    }
    int mid = (b + e) >> 1;
    if (ql <= mid) upd(lc, b, mid, ql, qr, v);
    if(qr > mid) upd(rc, mid + 1, e, ql, qr, v);
  }
  // can be generalized to any rollback structure
  void dfs(int n, int b, int e, int root, int eg) {
    int sz = t[n].size(), init = pst.T, croot = root;
    for(auto u : t[n]) croot = pst.upd(croot, 1, eg, u.a, u.b, u.h);

    if(b == e) {  // query ans
        if(!(ask[b][0] == 0 && ask[b][1] == 0))
            ans[b] = pst.query(croot, 1, eg, ask[b][0], ask[b][1]);
    } else {
        int mid = (b+e) >> 1;
        dfs(lc, b, mid, croot, eg); dfs(rc, mid+1, e, croot, eg); 
    }
    pst.T = init; // rollback
  }
  #undef lc 
  #undef rc 
};