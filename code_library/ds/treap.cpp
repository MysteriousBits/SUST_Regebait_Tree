struct ImplicitTreap {
  struct Node { int l, r, sz, sum, val, priority, lazy; };
  vector<Node> tree;
  mt19937 rnd;
  ImplicitTreap(int max_nodes = 0) {
    rnd.seed(chrono::steady_clock::now().time_since_epoch().count());
    if (max_nodes > 0) tree.reserve(max_nodes);
  }
  int getSize(int t) { return t == -1 ? 0 : tree[t].sz; }
  int getSum(int t) { return t == -1 ? 0 : tree[t].sum; }
  void applyLazy(int t, int add) {
    if (t == -1) return;
    tree[t].val += add; tree[t].sum += tree[t].sz * add; tree[t].lazy += add;
  }
  void pull(int t) {
    if (t == -1) return;
    tree[t].sz = 1 + getSize(tree[t].l) + getSize(tree[t].r);
    tree[t].sum = tree[t].val + getSum(tree[t].l) + getSum(tree[t].r);
  }
  void push(int t) {
    if (t == -1 || tree[t].lazy == 0) return;
    applyLazy(tree[t].l, tree[t].lazy); applyLazy(tree[t].r, tree[t].lazy);
    tree[t].lazy = 0;
  }
  int newNode(int val) {
    tree.push_back({-1, -1, 1, val, val, (int)rnd(), 0});
    return tree.size() - 1;
  }
  pair<int, int> split(int t, int k) {
    if (t == -1) return {-1, -1};
    push(t);
    if (getSize(tree[t].l) >= k) {
      auto res = split(tree[t].l, k);
      tree[t].l = res.second; pull(t);
      return {res.first, t};
    } else {
      auto res = split(tree[t].r, k - getSize(tree[t].l) - 1);
      tree[t].r = res.first; pull(t);
      return {t, res.second};
    }
  }
  int merge(int a, int b) {
    if (a == -1) return b;
    if (b == -1) return a;
    if (tree[a].priority > tree[b].priority) {
      push(a); tree[a].r = merge(tree[a].r, b); pull(a);
      return a;
    } else {
      push(b); tree[b].l = merge(a, tree[b].l); pull(b);
      return b;
    }
  }
  int insert(int root, int pos, int val) {
    int nn = newNode(val);
    auto [L, R] = split(root, pos);
    return merge(merge(L, nn), R);
  }
  int erase(int root, int pos) {
    auto [L, R] = split(root, pos);
    auto [p, q] = split(R, 1);
    return merge(L, q);
  }
  void show(int t) {
    if (t == -1) return;
    push(t); show(tree[t].l);
    cout << tree[t].val << " "; show(tree[t].r);
  }
};
