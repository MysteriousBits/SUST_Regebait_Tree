#define INFL (ll) 1e18
struct MCMF {
  struct Edge { int u, v; ll oc, cap, cost; };
  int s, t, n;
  vector<vector<int>> g;
  vector<Edge> edges;
  vector<ll> dist, p; vector<int> par;

  MCMF(int n, int s, int t) : s(s), t(t), n(n) { g.resize(n + 1); }

  void add_edge(int u, int v, ll cap, ll cost) {
    g[u].pb(edges.size()); g[v].pb(edges.size() + 1);
    edges.pb({u, v, cap, cap, cost}); edges.pb({v, u, 0, 0, -cost});
  }
  void setpot() {
    p.assign(n + 1, INFL); p[s] = 0;
    for (int i = 0; i < n; i++) for (auto& e : edges)
      if (e.cap && p[e.u] != INFL) p[e.v] = min(p[e.v], p[e.u] + e.cost);
  }
  bool dij() {
    dist.assign(n + 1, INFL); dist[s] = 0;
    vector<bool> done(n + 1); par.assign(n + 1, -1);
    priority_queue<pair<ll,int>> pq; pq.push({0, s});
    while (!pq.empty()) {
      int u = pq.top().second; pq.pop();
      if (done[u]) continue;
      p[u] += dist[u]; done[u] = true;
      for (int id : g[u]) {
        auto& e = edges[id];
        ll d = e.cost + p[u] - p[e.v];
        if (!done[e.v] && e.cap && d < dist[e.v])
          par[e.v] = id, dist[e.v] = d, pq.push({-d, e.v});
      }
    }
    return dist[t] != INFL;
  }
  pair<ll,ll> min_cost_flow() {
    setpot();
    ll f = 0, mc = 0;
    while (dij()) {
      ll mn = INFL;
      for (int u = t; u != s; u = edges[par[u]].u)
        mn = min(mn, edges[par[u]].cap);
      f += mn; mc += mn * p[t];
      for (int u = t; u != s; u = edges[par[u]].u)
        edges[par[u]].cap -= mn, edges[par[u] ^ 1].cap += mn;
    }
    return {f, mc};
  }
  // flow on edge id (0-based)
  ll flow(int id) { return edges[id << 1].oc - edges[id << 1].cap; }
};