struct Line {
  mutable int64_t m, b, p;
  bool operator<(const Line& o) const { return m < o.m; }
  bool operator<(int64_t x) const { return p < x; }
};
struct CHT : multiset<Line, less<>> {
  bool isMax;
  CHT(bool _isMax = true) { isMax = _isMax; }
  static int64_t div(int64_t a, int64_t b) {
    return a / b - ((a ^ b) < 0 && a % b);
  }
  bool isect(iterator x, iterator y) {
    if (y == end()) {
      x->p = LLONG_MAX;
      return false;
    }
    if (x->m == y->m) {
      x->p = (x->b > y->b ? LLONG_MAX : LLONG_MIN);
    } else {
      x->p = div(y->b - x->b, x->m - y->m);
    }
    return x->p >= y->p;
  }
  pair<int64_t, int64_t> convert(int64_t m, int64_t b) {
    if (isMax) return {m, b};
    return {-m, -b};
  }
  void add(int64_t m, int64_t b) {
    tie(m, b) = convert(m, b);
    auto z = insert({m, b, 0});
    auto y = z++;
    auto x = y;
    while (isect(y, z)) z = erase(z);
    if (x != begin() && isect(--x, y)) {
      isect(x, y = erase(y));
    }
    while ((y = x) != begin() && (--x)->p >= y->p) {
      isect(x, erase(y));
    }
  }
  static int64_t eval(const Line& l, int64_t x) {
    return (int64_t)((__int128)l.m * x + l.b);
  }
  int64_t query(int64_t x) {
    assert(!empty());
    auto l = *lower_bound(x);
    int64_t ans = eval(l, x);
    if (!isMax) ans = -ans;
    return ans;
  }
};