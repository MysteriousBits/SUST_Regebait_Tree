struct GeneralMatching {
  int n;
  vector<pair<int, int>> edges;
  GeneralMatching(int n) : n(n) {}
  // 1-indexed edge insertion
  void add_edge(int u, int v) {
    edges.push_back({u, v});
  }
  // Mucha Sankowski's algorihtm - N^3
  // Returns {max_matching_count, vector<pair<u, v>>}
  pair<int, vector<pair<int, int>>> solve() {
    Mat mat(n, n), A;
    for (auto pa : edges) {
      int a = pa.first - 1, b = pa.second - 1;
      int r = rand() % mod;
      mat.a[a][b] = r;
      mat.a[b][a] = (mod - r) % mod;
    }
    int r = matInv(mat, A), M = 2 * n - r, fi, fj;
    assert(r % 2 == 0);

    if (M != n) do {
      Mat new_mat(M, M);
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) new_mat.a[i][j] = mat.a[i][j];
        for (int j = n; j < M; ++j) {
          int r = rand() % mod;
          new_mat.a[i][j] = r;
          new_mat.a[j][i] = (mod - r) % mod;
        }
      }
      mat = new_mat;
    } while (matInv(mat, A) != M);

    vector<int> has(M, 1);
    vector<pair<int, int>> ret;
    for (int it = 0; it < M / 2; ++it) {
      for (int i = 0; i < M; ++i) if (has[i])
        for (int j = i + 1; j < M; ++j) if (A.a[i][j] && mat.a[i][j]) {
          fi = i; fj = j; goto done;
        }
      assert(0);
      done:
      if (fj < n) ret.push_back({fi + 1, fj + 1});
      has[fi] = has[fj] = 0;
      for (int sw = 0; sw < 2; ++sw) {
        long long a = modpow(A.a[fi][fj], mod - 2);
        for (int i = 0; i < M; ++i) if (has[i] && A.a[i][fj]) {
          long long b = A.a[i][fj] * a % mod;
          for (int j = 0; j < M; ++j) A.a[i][j] = (A.a[i][j] - A.a[fi][j] * b) % mod;
        }
        swap(fi, fj);
      }
    }
    return {(int)ret.size(), ret};
  }
};