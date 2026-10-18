struct CHT { // min query, upper hull (left to right)
  struct Line { ll m, c; ll f(ll x) { return m * x + c; } };
  deque<Line> hull;

  bool bad(Line l1, Line l2, Line l3) {
    return (__int128)(l3.c - l1.c) * (l1.m - l2.m)
        <= (__int128)(l2.c - l1.c) * (l1.m - l3.m);
  }
  void add(ll m, ll c) { // lines must be added with decreasing slope
    Line l = {m, c};
    if (!hull.empty() && hull.back().m == m) {
      if (c >= hull.back().c) return;
      hull.pop_back();
    }
    while (hull.size() > 1 && bad(hull[hull.size()-2], hull.back(), l))
      hull.pop_back();
    hull.push_back(l);
  }
  ll query(ll x) { // O(log n), arbitrary x
    int l = 0, r = hull.size() - 1;
    while (l < r) {
      int mid = (l + r) / 2;
      if (hull[mid].f(x) > hull[mid+1].f(x)) l = mid + 1;
      else r = mid;
    }
    return hull[l].f(x);
  }
  ll query_monotone(ll x) { // O(1) amortized, x must be increasing
    while (hull.size() > 1 && hull[0].f(x) > hull[1].f(x))
      hull.pop_front();
    return hull[0].f(x);
  }
};