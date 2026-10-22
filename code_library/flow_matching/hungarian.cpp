template <class T = long long>
struct Hungarian {
  int n, m;
  T INF;
  vector<vector<T>> C;
  Hungarian(int n, int m, T inf = 1e16) : n(n), m(m), INF(inf), C(n + 1, vector<T>(m + 1, inf)) {}
  void add_edge(int u, int v, T weight) {
    C[u][v] = min(C[u][v], weight); // -weight for Maximum
  }
  // {max_cost, match} 1 indexed !!! (requires n <= m) !!!
  pair<T, vector<int>> solve() {
    int i = n, c = 0, s = 0, r = 0;
    vector<T> dist(m+1), pot(m+1, 0);
    vector<int> match(n+1, 0), rev(m+1, 0), cols(m+1), prev(m+1);
    T d = 0, nd, cost = 0;
    while (i) {
      for (int c = 1; c <= m; ++c) dist[c] = C[i][c], cols[c] = c, prev[c] = i;
      for (s = 1;;) {
        for (int j = s; j <= m; ++j) {
          c = cols[j], nd = dist[c] - pot[c];
          if (j == s || d > nd) d = nd, swap(cols[s], cols[j]);
        }
        if ((r = rev[c = cols[s++]]) == 0) break;
        for (int j = 1; j <= m; ++j) if (dist[j] > (nd = C[r][j] - C[r][c] + dist[c]))
          dist[j] = nd, prev[j] = r;
      }
      cost += dist[c];
      while (--s) pot[cols[s]] = dist[cols[s]] - d;
      for (; r != i; swap(c, match[r]))
        r = rev[c] = prev[c];
      i--;
    }
    return {cost, match}; // -cost for maximum
  }
};