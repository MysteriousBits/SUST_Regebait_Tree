const int LOG_K = 60;  // Adjust as needed
struct XorBasis {
  vector<int64_t> basis;
  int64_t N = 0, tmp = 0;
  void add(int64_t x) {
    N++;
    tmp |= x;
    for (auto& i : basis) {
      x = min(x, x ^ i);
    }
    if (!x) return;
    for (auto& i : basis) {
      if ((i ^ x) < i) {
        i ^= x;
      }
    }
    basis.push_back(x);
    sort(basis.begin(), basis.end());
  }
  int64_t size() { return (int64_t)basis.size(); }
  void clear() {
    N = 0;
    tmp = 0;
    basis.clear();
  }
  bool possible(int64_t x) {
    for (auto& i : basis) {
      x = min(x, x ^ i);
    }
    return !x;
  }
  int64_t maxxor(int64_t x = 0) {
    for (auto& i : basis) {
      x = max(x, x ^ i);
    }
    return x;
  }
  int64_t minxor(int64_t x = 0) {
    for (auto& i : basis) {
      x = min(x, x ^ i);
    }
    return x;
  }
  int64_t cntxor(int64_t x) {
    if (!possible(x)) return 0;
    return (1LL << (N - size()));
  }
  int64_t sumOfAll() {
    int64_t ans = tmp * (1LL << (N - 1));
    return ans;
  }
  int64_t kth(int64_t k) {
    int64_t sz = size();
    if (k > (1LL << sz)) return -1;
    k--;
    int64_t ans = 0;
    for (int64_t i = 0; i < sz; i++) {
      if (k >> i & 1) {
        ans ^= basis[i];
      }
    }
    return ans;
  }
};