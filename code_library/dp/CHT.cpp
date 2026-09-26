struct CHT {
  deque<pair<ll, ll>> hull;
  bool increasing; // true for increasing slope
  CHT(bool increasing) : increasing(increasing) {}
  ll f(ll x, int i) { return hull[i].first * x + hull[i].second; }
  bool bad(pair<ll, ll> l1, pair<ll, ll> l2, pair<ll, ll> l3) {
    __int128 lhs = (__int128)(l1.first - l3.first) * (l2.second - l1.second);
    __int128 rhs = (__int128)(l1.first - l2.first) * (l3.second - l1.second);
    return increasing ? lhs >= rhs : lhs <= rhs;
  }
  void addline(ll m, ll c) {
    if (!hull.empty() && hull.back().first == m) {
      if (c >= hull.back().second) return;
      hull.pop_back();
    }
    while (hull.size() > 1 && bad({m, c}, hull.back(), hull[hull.size() - 2]))
      hull.pop_back();
    hull.push_back({m, c});
  }
  ll query_monotonic(ll x) { // works O(1) if slope decreasing, x increasing or vice-versa
    while (hull.size() > 1 && f(x, 0) >= f(x, 1)) hull.pop_front();
    return f(x, 0);
  }
  ll query(ll x) { // arbitrary query with binary search, O(logn)
    if (hull.size() == 1) return f(x, 0);
    int l = 0, r = hull.size() - 2;
    while (l < r) {
      int mid = (l + r + 1) / 2;
      if (f(x, mid) > f(x, mid + 1))
        l = mid;
      else
        r = mid - 1;
    }
    return f(x, l + 1);
  }
};