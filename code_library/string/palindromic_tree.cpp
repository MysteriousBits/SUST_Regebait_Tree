struct EERTREE {
  struct node {
    int nxt[26], len, st, en, link, cnt, oc;
    int diff, slink; // For O(N log N) / O(N) Palindrome DP
  };
  string s;
  vector<node> t;
  int sz, last;
  void init(string _s) {
    s = _s;
    t.assign(s.size() + 9, {});
    sz = last = 2;
    t[1].len = -1; t[1].link = 1;
    t[2].len = 0;  t[2].link = 1;
  }
  int get_link(int u, int i) {
    while (i - 1 - t[u].len < 0 || s[i - 1 - t[u].len] != s[i]) u = t[u].link;
    return u;
  }
  bool extend(int i) {
    int c = s[i] - 'a', u = get_link(last, i);
    if (t[u].nxt[c]) return last = t[u].nxt[c], t[last].oc++, 0;
    
    last = ++sz;
    t[sz].len = t[u].len + 2; t[sz].en = i; t[sz].st = i - t[sz].len + 1;
    t[sz].oc = 1; t[u].nxt[c] = sz;
    t[sz].link = (t[sz].len == 1) ? 2 : t[get_link(t[u].link, i)].nxt[c];
    t[sz].cnt = 1 + t[t[sz].link].cnt;
    // Series link setup for fast DP
    t[sz].diff = t[sz].len - t[t[sz].link].len;
    t[sz].slink = (t[sz].diff == t[t[sz].link].diff) ? t[t[sz].link].slink : t[sz].link;
    return 1;
  }
  void calc_oc() {
    for (int i = sz; i > 2; i--) t[t[i].link].oc += t[i].oc;
  }
  // --- Utility Methods ---
  void build() {
    for (int i = 0; i < (int)s.size(); i++) extend(i);
    calc_oc();
  }
  int count_distinct() { return sz - 2; }
  long long count_total() { // Requires calc_oc() / build() to be called first
    long long tot = 0;
    for (int i = 3; i <= sz; i++) tot += t[i].oc;
    return tot;
  }
  string get_palindrome(int u) {
    return s.substr(t[u].st, t[u].len);
  }
};