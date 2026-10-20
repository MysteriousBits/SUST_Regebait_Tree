struct SuffixAutomaton {
  struct node { int len, link, fpos; map<char, int> nxt; };
  int sz = 1, last = 0;
  vector<node> t;
  vector<int> term;
  vector<long long> dp;
  vector<vector<int>> g;

  SuffixAutomaton(int n) : t(2 * n), term(2 * n, 0), dp(2 * n, -1), g(2 * n) {
    t[0].link = -1;
  }
  void extend(char c) {
    int p = last, q, clone, cur;
    if (t[p].nxt.count(c)) {
      q = t[p].nxt[c];
      if (t[q].len == t[p].len + 1) { last = q; return; }
      clone = sz++; t[clone] = t[q]; t[clone].len = t[p].len + 1;
      t[q].link = last = clone;
      while (p != -1 && t[p].nxt[c] == q) t[p].nxt[c] = clone, p = t[p].link;
      return;
    }
    cur = last = sz++;
    t[cur].len = t[p].len + 1; t[cur].fpos = t[cur].len;
    while (p != -1 && !t[p].nxt.count(c)) t[p].nxt[c] = cur, p = t[p].link;
    if (p == -1) t[cur].link = 0;
    else {
      q = t[p].nxt[c];
      if (t[p].len + 1 == t[q].len) t[cur].link = q;
      else {
        clone = sz++; t[clone] = t[q]; t[clone].len = t[p].len + 1;
        while (p != -1 && t[p].nxt[c] == q) t[p].nxt[c] = clone, p = t[p].link;
        t[q].link = t[cur].link = clone;
      }
    }
  }
  void build(const string &s) {
    for (char x : s) extend(x), term[last] = 1;
    for (int i = 1; i < sz; i++) g[t[i].link].push_back(i);
  }
  long long cnt(int i) {
    if (dp[i] != -1) return dp[i];
    dp[i] = term[i];
    for (int x : g[i]) dp[i] += cnt(x);
    return dp[i];
  }
};