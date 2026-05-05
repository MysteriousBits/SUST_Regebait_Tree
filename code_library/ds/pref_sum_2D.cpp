template<typename T>
struct PrefixSum2D {
  vector<vector<T>> p;
  int rows, cols;

  T combine(T x, T y) { return x + y; }

  void build(vector<vector<T>>& a) {
    rows = a.size(); cols = a[0].size();
    p.assign(rows + 1, vector<T>(cols + 1, 0));
    for(int i = 1; i <= rows; ++i)
      for(int j = 1; j <= cols; ++j)
        p[i][j] = a[i-1][j-1] + p[i-1][j] + p[i][j-1] - p[i-1][j-1];
  }

  // query sum over [r1,c1]..[r2,c2] (1-indexed)
  T query(int r1, int c1, int r2, int c2) {
    return p[r2][c2] - p[r1-1][c2] - p[r2][c1-1] + p[r1-1][c1-1];
  }
};