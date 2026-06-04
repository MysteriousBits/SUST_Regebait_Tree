struct mos_update {
  ll a[100005];
  ll ans;
  mos_update() { /* ... */ }
  void add(int ind, int end, int L, int R) { /* ... */ }
  void del(int ind, int end, int L, int R) { /* ... */ }
  void apply(int pos, int val, int L, int R) {
    if (L <= pos && pos <= R) { 
      del(pos, -1, L, R); a[pos] = val; add(pos, -1, L, R); 
    } else { 
      a[pos] = val; 
    }
  }
  vector<ll> mo(vector<vector<int>>& Q, vector<vector<int>>& U, int n) {
    int L = 1, R = 0, T = 0;
    ans = 0;
    int blk = max(1, (int)pow(Q.size(), 0.666));
    vector<int> s(Q.size());
    vector<ll> res(Q.size());
    iota(s.begin(), s.end(), 0);
    sort(s.begin(), s.end(), [&](int i, int j) {
      int li = Q[i][0] / blk, lj = Q[j][0] / blk;
      if (li != lj) return li < lj;
      int ri = Q[i][1] / blk, rj = Q[j][1] / blk;
      if (ri != rj) return (li & 1) ? ri < rj : ri > rj;
      return (ri & 1) ? Q[i][2] < Q[j][2] : Q[i][2] > Q[j][2];
    });
    for (int qi : s) {
      int ql = Q[qi][0], qr = Q[qi][1], qt = Q[qi][2];
      while (T < qt) { apply(U[T][0], U[T][2], L, R); T++; }
      while (T > qt) { --T; apply(U[T][0], U[T][1], L, R); }
      while (L > ql) { --L; add(L, 0, L, R); }
      while (R < qr) { ++R; add(R, 1, L, R); }
      while (L < ql) { del(L, 0, L, R); L++; }
      while (R > qr) { del(R, 1, L, R); R--; }
      res[qi] = ans;
    }
    return res;
  }
};