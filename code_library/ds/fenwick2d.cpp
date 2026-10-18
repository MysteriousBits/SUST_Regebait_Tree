struct FT2 {
  int n; vector<FT> ft;
  vector<vector<int>> ys; 
  FT2(int limx) : n(limx + 1), ys(limx + 1) {}
  void fakeUpdate(int x, int y) {
    for (; x < n; x += x & -x) {
      ys[x].push_back(y);
    }
  }
  void init() {
    ft.assign(ys.size(), FT(0));
    for (int i = 0; i < n; ++i) {
      sort(ys[i].begin(), ys[i].end());
      ys[i].erase(unique(ys[i].begin(), ys[i].end()), ys[i].end());
      ft[i] = FT(ys[i].size());
    }
  }
  int ind(int x, int y) {
    return upper_bound(ys[x].begin(), ys[x].end(), y) - ys[x].begin(); 
  }
  void update(int x, int y, ll dif) {
    for (; x < n; x += x & -x)
      ft[x].update(ind(x, y), dif);
  }
  ll query(int x, int y) {
    ll sum = 0;
    for (; x > 0; x -= x & -x) {
      sum += ft[x].query(ind(x, y));
    }
    return sum;
  }
  ll query(int x1, int y1, int x2, int y2) {
    return query(x2,y2) - query(x1-1, y2) -
        query(x2, y1-1) + query(x1-1, y1-1);
  }
};