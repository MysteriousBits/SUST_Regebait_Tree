struct AhoCorasick {
  enum {alpha = 26, first = 'A'}; // change this!
  struct Node {
    int back, next[alpha], start = -1, end = -1, nmatches = 0;
    Node(int v) { memset(next, v, sizeof(next)); }
  };
  vector<Node> N;
  vector<int> backp;

  void insert(string& s, int j) {
    assert(!s.empty());
    int n = 0;
    for (char c : s) {
      int& m = N[n].next[c - first];
      if (m == -1) { n = m = N.size(); N.emplace_back(-1); }
      else n = m;
    }
    if (N[n].end == -1) N[n].start = j;
    backp.push_back(N[n].end);
    N[n].end = j;
    N[n].nmatches++;
  }

  AhoCorasick(vector<string>& pat) : N(1, -1) {
    for (int i = 0; i < (int)pat.size(); ++i) insert(pat[i], i);
    N[0].back = N.size();
    N.emplace_back(0);
    queue<int> q;
    for (q.push(0); !q.empty(); q.pop()) {
      int n = q.front(), prev = N[n].back;
      for (int i = 0; i < alpha; ++i) {
        int &ed = N[n].next[i], y = N[prev].next[i];
        if (ed == -1) ed = y;
        else {
          N[ed].back = y;
          (N[ed].end == -1 ? N[ed].end : backp[N[ed].start]) = N[y].end;
          N[ed].nmatches += N[y].nmatches;
          q.push(ed);
        }
      }
    }
  }
  // returns HEADS of all the occurances.
  vector<int> find(string word) {
    int n = 0;
    vector<int> res; res.reserve(word.size());
    // ll cnt = 0;
    for (char c : word) {
      n = N[n].next[c - first];
      res.push_back(N[n].end);  // cnt += N[n].nmatches;
    }
    return res;
  }
  // reach[i][j] = true iff pat[i] is a substring of pat[j]
  template <size_t MAXN = 1000>
  vector<bitset<MAXN>> allStringRelation(vector<string>& pat) {
    int sz = pat.size(); vector<bitset<MAXN>> reach(sz);
    for (int i = 0; i < sz; ++i) {
      int n = 0;
      for (char c : pat[i]) {
        n = N[n].next[c - first]; int m = N[n].end;
        if (m != -1) {
          if (m != i) reach[m].set(i);
          else if (int fail = N[n].back; N[fail].end != -1) reach[N[fail].end].set(i);
        } } }
    for (int k = 0; k < sz; ++k) for (int i = 0; i < sz; ++i)
        if (reach[i][k]) reach[i] |= reach[k];
    return reach;
  }
};