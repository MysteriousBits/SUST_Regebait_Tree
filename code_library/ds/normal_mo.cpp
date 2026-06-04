void add(int ind, int end, int L, int R) { /* ... */ }
void del(int ind, int end, int L, int R) { /* ... */ }  
int calc(int L, int R) { /* ... */ }                     
vector<int> mo(vector<pair<int, int>>& Q) {
  int L = 1, R = 0, blk = 350;
  vector<int> s(Q.size()), res(Q.size());
  iota(s.begin(), s.end(), 0);
  sort(s.begin(), s.end(), [&](int i, int j) {
    int bi = Q[i].first / blk;
    int bj = Q[j].first / blk;
    if (bi != bj) return bi < bj;
    if (bi & 1) return Q[i].second < Q[j].second;
    return Q[i].second > Q[j].second;
  });
  for (int qi : s) {
    pair<int, int> q = Q[qi];
    int ql = q.first;
    int qr = q.second;  
    while (L > ql) { --L; add(L, 0, L, R); }
    while (R < qr) { ++R; add(R, 1, L, R); }
    while (L < ql) { del(L, 0, L, R); L++; }
    while (R > qr) { del(R, 1, L, R); R--; }
    res[qi] = calc(L, R);
  }
  return res;
}