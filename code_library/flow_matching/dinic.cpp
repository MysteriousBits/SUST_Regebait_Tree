const int64_t inf = 1LL << 60; 
struct Dinic {
   struct Edge {
      int to, rev;
      int64_t flow, w;
      int id;
   };
   int n, s, t, mxid;
   vector<int> d, done;
   vector<int64_t> flow_through;
   vector<vector<Edge>> g;
   Dinic() {}
   Dinic(int _n) {
      n = _n + 10;
      mxid = 0;
      g.resize(n);
   }
   void add_edge(int u, int v, int64_t w, int id = -1) {
      Edge a = {v, (int)g[v].size(), 0, w, id};
      Edge b = {u, (int)g[u].size(), 0, 0, -2}; // cap(b) = w for bidirectional
      g[u].emplace_back(a);
      g[v].emplace_back(b);
      if (id >= 0) mxid = max(mxid, id);
   }
   bool bfs() {
      d.assign(n, -1);
      d[s] = 0;
      queue<int> q;
      q.push(s);
      while (!q.empty()) {
         int u = q.front();
         q.pop();
         for (auto &e : g[u]) {
            int v = e.to;
            if (d[v] == -1 && e.flow < e.w) {
               d[v] = d[u] + 1;
               q.push(v);
            }
         }
      }
      return d[t] != -1;
   }
   int64_t dfs(int u, int64_t flow) {
      if (u == t) return flow;
      for (int &i = done[u]; i < (int)g[u].size(); i++) {
         Edge &e = g[u][i];
         if (e.w <= e.flow) continue;
         int v = e.to;
         if (d[v] == d[u] + 1) {
            int64_t nw = dfs(v, min(flow, e.w - e.flow));
            if (nw > 0) {
               e.flow += nw;
               g[v][e.rev].flow -= nw;
               return nw;
            }
         }
      }
      return 0;
   }
   int64_t max_flow(int _s, int _t) {
      s = _s;
      t = _t;
      int64_t flow = 0;
      while (bfs()) {
         done.assign(n, 0);
         while (int64_t nw = dfs(s, inf)) {
            flow += nw;
         }
      }
      flow_through.assign(mxid+10,int64_t(0));
      for (int i = 0; i < n; i++) {
         for (auto &e : g[i]) {
            if (e.id >= 0) {
               flow_through[e.id] = e.flow;
            }
         }
      }
      return flow;
   }
};
