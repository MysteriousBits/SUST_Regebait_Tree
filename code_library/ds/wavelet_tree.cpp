struct wavelet_tree {
    int lo, hi;
    wavelet_tree *l, *r;
    vector<int> b, c;
    wavelet_tree() {
        lo = hi = 0;
        l = r = NULL;
    }
    void init(int *from, int *to, int x, int y) {
        lo = x, hi = y;
        if (from >= to) return;
        int mid = (lo + hi) >> 1;
        auto f = [mid](int x) { return x <= mid; };
        b.reserve(to - from + 1);
        c.reserve(to - from + 1);
        b.push_back(0);
        c.push_back(0);
        for (auto it = from; it != to; ++it) {
            b.push_back(b.back() + f(*it));
            c.push_back(c.back() + (*it));
        }
        if (hi == lo) return;
        auto pivot = stable_partition(from, to, f);
        l = new wavelet_tree(); l->init(from, pivot, lo, mid);
        r = new wavelet_tree(); r->init(pivot, to, mid + 1, hi);
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
        return this->l->LTE(lb + 1, rb, k) + this->r->LTE(l - lb, r - rb, k);
    }
    int count(int l, int r, int k) {
        if (l > r || k < lo || k > hi) return 0;
        if (lo == hi) return r - l + 1;
        int lb = b[l - 1], rb = b[r], mid = (lo + hi) >> 1;
        if (k <= mid) return this->l->count(lb + 1, rb, k);
        return this->r->count(l - lb, r - rb, k);
    }
    int sum(int l, int r, int k) {
        if (l > r || k < lo) return 0;
        if (hi <= k) return c[r] - c[l - 1];
        int lb = b[l - 1], rb = b[r];
        return this->l->sum(lb + 1, rb, k) + this->r->sum(l - lb, r - rb, k);
    }
    ~wavelet_tree() { delete l; delete r; }
};
wavelet_tree t;