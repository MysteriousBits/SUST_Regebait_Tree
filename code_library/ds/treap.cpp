const int id = 0, lazy_id = 0;
struct Node {
    int val, sum, lazy = 0;
    int pri, sz = 1;
    Node *l, *r;
    Node(int v, int p) : val(v), sum(v), pri(p) { l = r = nullptr; }
};
mt19937 rnd{(uint32_t)chrono::steady_clock::now().time_since_epoch().count()};
 
int sz(Node* n) { return n ? n->sz : 0; }
int sum(Node* n) { return n ? n->sum : id; }
int combine(int x, int y) { return x + y; }
 
void apply(Node* n, int v) { // change here
    if (!n) return;
    n->val += v; n->lazy += v; n->sum += v * n->sz;
}
void push(Node* n) {
    if (n->lazy != lazy_id) { apply(n->l, n->lazy); apply(n->r, n->lazy); n->lazy = 0; }
}
void pull(Node* n) {
    n->sz = sz(n->l) + sz(n->r) + 1;
    n->sum = combine(sum(n->l), sum(n->r)) + n->val;
}
pair<Node*, Node*> split(Node* n, int k) { // splits into 1..k | k+1..n
    if (!n) return {nullptr, nullptr};
    push(n);
    int sl = sz(n->l);  // n->val for key
    if (sl < k) {
      auto [a, b] = split(n->r, k - sl - 1);
      n->r = a; pull(n); return {n, b};
    } // else for split_by_key
    auto [a, b] = split(n->l, k);
    n->l = b; pull(n); return {a, n};
}
Node* merge(Node* a, Node* b) {
    if (!a) return b;
    if (!b) return a;
    if (a->pri > b->pri) { push(a); a->r = merge(a->r, b); pull(a); return a; }
    push(b); b->l = merge(a, b->l); pull(b); return b;
}
// Merges two OVERLAPPING sorted treaps O(K log(N/K))
Node* meld(Node* u, Node* v) {
    if (!u || !v) return u ? u : v;
    if (u->pri < v->pri) swap(u, v); 
    auto [l, r] = split_by_key(v, u->val);
    u->l = meld(u->l, l);
    u->r = meld(u->r, r);
    pull(u);
    return u;
}
void clear(Node* n) {
    if (!n) return;
    clear(n->l); clear(n->r); delete n;
}
Node* insert(Node* root, int val, int pos = 0) {
    Node* n = new Node(val, rnd());
    pos = pos ? pos - 1 : sz(root);
    auto [a, b] = split(root, pos);
    root = merge(merge(a, n), b);
    return root;
}
Node* erase(Node* root, int pos) { // 1-based
    auto [a, b] = split(root, pos);
    auto [c, d] = split(a, pos - 1);
    root = merge(c, b); if (d) delete d;
    return root;
}
int get(int i, Node* n) { // 1-based index
    if(sz(n) < i) return -1;
    push(n);
    int id = sz(n->l) + 1;  //
    if (id == i) return n->val;
    return id < i ? get(i - id, n->r) : get(i, n->l);
}
int search(int val, Node* n) {  // in sorted
    if(!n) return 0;
    push(n);
    int id = sz(n->l) + 1;
    int v = n->val;
    // cout << id << ' ' << v << '\n';
    if(v < val) return id+search(val, n->r); 
    else return search(val, n->l);
}