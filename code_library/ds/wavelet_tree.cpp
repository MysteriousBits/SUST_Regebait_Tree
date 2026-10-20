struct wavelet_tree {
  int lo, hi;
  wavelet_tree *l = nullptr, *r = nullptr;
  vector<int> b, c;

  wavelet_tree() : lo(0), hi(0) {}

  void init(int *from, int *to, int x, int y) {
    lo = x; hi = y;
    if (from >= to) return;
    int mid = lo + (hi - lo) / 2;
    auto f = [mid](int val) { return val <= mid; };
    
    b.reserve(to - from + 1); c.reserve(to - from + 1);
    b.push_back(0); c.push_back(0);
    for (auto it = from; it != to; ++it) {
      b.push_back(b.back() + f(*it));
      c.push_back(c.back() + *it);
    }
    if (lo == hi) return;

    auto pivot = stable_partition(from, to, f);
    (l = new wavelet_tree())->init(from, pivot, lo, mid);
    (r = new wavelet_tree())->init(pivot, to, mid + 1, hi);
  }

  int kth(int l, int r, int k) {
    if (l > r) return 0;
    if (lo == hi) return lo;
    int inLeft = b[r] - b[l - 1], lb = b[l - 1], rb = b[r];
    if (k <= inLeft) return this->l->kth(lb + 1, rb, k);
    return this->r->kth(l - lb, r - rb, k - inLeft);
  }

  int LTE(int l, int r, int k) {
    if (l > r || k < lo) return 0;
    if (hi <= k) return r - l + 1;
    int lb = b[l - 1], rb = b[r];
    return l->LTE(lb + 1, rb, k) + r->LTE(l - lb, r - rb, k);
  }

  int count(int l, int r, int k) {
    if (l > r || k < lo || k > hi) return 0;
    if (lo == hi) return r - l + 1;
    int lb = b[l - 1], rb = b[r], mid = lo + (hi - lo) / 2;
    if (k <= mid) return l->count(lb + 1, rb, k);
    return r->count(l - lb, r - rb, k);
  }

  int sum(int l, int r, int k) {
    if (l > r || k < lo) return 0;
    if (hi <= k) return c[r] - c[l - 1];
    int lb = b[l - 1], rb = b[r];
    return l->sum(lb + 1, rb, k) + r->sum(l - lb, r - rb, k);
  }

  ~wavelet_tree() { delete l; delete r; }
};