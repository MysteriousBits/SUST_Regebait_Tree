struct Node {
  int u;
  ll dist;
  bool operator<(const Node& v) const { return dist > v.dist; }
};
vector<ll> dijkstra(int start, vector<VPI>& adj) {
  vector<ll> dis(adj.size(), INFL);
  priority_queue<Node> q;
  dis[start] = 0;
  q.push({start, 0});
  while (!q.empty()) {
    Node node = q.top();
    int u = node.u;
    q.pop();
    if (dis[u] < node.dist) continue;
    for (auto e : adj[u]) {
      if (node.dist + e.ss < dis[e.ff]) {
        dis[e.ff] = node.dist + e.ss;
        q.push({e.ff, dis[e.ff]});
      }
    }
  }
  return dis;
}