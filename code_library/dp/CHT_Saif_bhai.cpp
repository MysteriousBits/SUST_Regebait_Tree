struct CHT {
  int ptr = 0;
  vector<int64_t> m, c;
  // (<=) : (decreasing + min) or, (increasing + max) 
  // (>=) : (decreasing + max) or, (increasing + min) 
  bool bad(int l1, int l2, int l3) {
    return (__int128_t)(c[l3] - c[l1]) * (m[l1] - m[l2]) <= (__int128_t)(c[l2] - c[l1]) * (m[l1] - m[l3]);
  }
  void add(int64_t _m, int64_t _c) {
    m.push_back(_m);
    c.push_back(_c);

    while (m.size() >= 3 && bad(m.size() - 3, m.size() - 2, m.size() - 1)) {
      m.erase(m.end() - 2);
      c.erase(c.end() - 2);
    }
  }
  inline int64_t f(int i, int64_t x) const {
    return m[i] * x + c[i];
  }
  int64_t query(int64_t x) {
    if (ptr >= (int)m.size()) ptr = m.size() - 1;

    while (ptr + 1 < (int)m.size() && f(ptr + 1, x) <= f(ptr, x)) {
      ptr++;
    }
    return f(ptr, x);
  }
  int64_t bs(int64_t x) {
    int lo = 0, hi = int(m.size()) - 1;
    while (lo < hi) {
      int mid = (lo + hi) / 2;

      if (f(mid, x) >= f(mid + 1, x)) { // max(<=) // min(>=)
        lo = mid + 1;
      } else {
        hi = mid;
      }
    }
    return f(lo, x);
  }
};