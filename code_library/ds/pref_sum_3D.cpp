template<typename T>
struct PrefixSum3D {
  vector<vector<vector<T>>> p;
  int X, Y, Z;

  T combine(T x, T y) { return x + y; }

  void build(vector<vector<vector<T>>>& a) {
    X = a.size(); Y = a[0].size(); Z = a[0][0].size();
    p.assign(X+1, vector<vector<T>>(Y+1, vector<T>(Z+1, 0)));
    for(int i = 1; i <= X; ++i)
      for(int j = 1; j <= Y; ++j)
        for(int k = 1; k <= Z; ++k)
          p[i][j][k] = a[i-1][j-1][k-1]
            + p[i-1][j][k] + p[i][j-1][k] + p[i][j][k-1]
            - p[i-1][j-1][k] - p[i-1][j][k-1] - p[i][j-1][k-1]
            + p[i-1][j-1][k-1];
  }

  // query sum over [x1,y1,z1]..[x2,y2,z2] (1-indexed)
  T query(int x1, int y1, int z1, int x2, int y2, int z2) {
    return p[x2][y2][z2]
      - p[x1-1][y2][z2] - p[x2][y1-1][z2] - p[x2][y2][z1-1]
      + p[x1-1][y1-1][z2] + p[x1-1][y2][z1-1] + p[x2][y1-1][z1-1]
      - p[x1-1][y1-1][z1-1];
  }
};