template<typename T>
struct ImplicitTreap {
  struct Node {
    T val, aggr, lazy = 0;
    int pri, sz = 1;
    bool rev = false;
    Node *l, *r;
    Node(T v, int p) : val(v), aggr(v), pri(p) { l = r = nullptr; }
  };
  Node* root = nullptr;
  T identity = 0, lazy_identity = 0; // change: 0 for sum, INF for min, etc.
  mt19937 rnd{(uint32_t)chrono::steady_clock::now().time_since_epoch().count()};
  ~ImplicitTreap() { clear(root); }
  int sz(Node* n) { return n ? n->sz : 0; }
  int size() { return sz(root); }
  T aggr(Node* n) { return n ? n->aggr : identity; }
  T combine(T x, T y) { return x + y; }
  void apply(Node* n, T v) { // change here
    if (!n) return;
    n->val += v; n->lazy += v; n->aggr += v * n->sz;
  }
  void push(Node* n) {
    if (n->rev) {
      if (n->l) n->l->rev ^= 1;
      if (n->r) n->r->rev ^= 1;
      swap(n->l, n->r); n->rev = false;
    }
    if (n->lazy != lazy_identity) { apply(n->l, n->lazy); apply(n->r, n->lazy); n->lazy = lazy_identity; }
  }
  void pull(Node* n) {
    n->sz = sz(n->l) + sz(n->r) + 1;
    n->aggr = combine(aggr(n->l), aggr(n->r)) + n->val;
  }
  pair<Node*, Node*> split(Node* n, int k) { // splits into 1..k | k+1..n
    if (!n) return {nullptr, nullptr};
    push(n);
    int sl = sz(n->l);
    if (sl < k) {
      auto [a, b] = split(n->r, k - sl - 1);
      n->r = a; pull(n); return {n, b};
    }
    auto [a, b] = split(n->l, k);
    n->l = b; pull(n); return {a, n};
  }
  Node* merge(Node* a, Node* b) {
    if (!a) return b;
    if (!b) return a;
    if (a->pri > b->pri) { push(a); a->r = merge(a->r, b); pull(a); return a; }
    push(b); b->l = merge(a, b->l); pull(b); return b;
  }
  template<typename F>
  auto seg(int l, int r, F f) {
    auto [a, b] = split(root, l - 1);
    auto [c, d] = split(b, r - l + 1);
    auto res = f(c);
    root = merge(merge(a, c), d);
    return res;
  }
  void modify(int l, int r, T v) { seg(l, r, [&](Node* c) { apply(c, v); return 0; }); }
  void reverse(int l, int r) { seg(l, r, [&](Node* c) { c->rev ^= 1; return 0; }); }
  T query(int l, int r) { return seg(l, r, [&](Node* c) { return c->aggr; }); }
  T get(int i, Node* n = nullptr) { // 1-based index
    n = n ? n : root; push(n);
    int id = sz(n->l) + 1;
    if (id == i) return n->val;
    return id < i ? get(i - id, n->r) : get(i, n->l);
  }
  void insert(T val, int pos = 0) { // 1-based, pos=0 means end
    Node* n = new Node(val, rnd());
    pos = pos ? pos - 1 : size();
    auto [a, b] = split(root, pos);
    root = merge(merge(a, n), b);
  }
  void erase(int pos) { // 1-based
    auto [a, b] = split(root, pos);
    auto [c, d] = split(a, pos - 1);
    root = merge(c, b); if (d) delete d;
  }
  void clear(Node* n) {
    if (!n) return;
    clear(n->l); clear(n->r); delete n;
  }
};