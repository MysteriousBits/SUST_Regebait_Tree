struct SuffixAutomaton {
  enum {alpha = 26, first = 'a'}; // change this!
  struct Node {
    // term -> whether the longest substr of this node is a proper prefix
    // end-occurance of the first position
    int len = 0, link = -1, fpos = 0, term = 0;
    long long occ = -1; // endpos size (occurance count)
    int next[alpha];
    Node(int v) { memset(next, v, sizeof(next)); }
  };
  vector<Node> N;
  vector<vector<int>> g;  // fail tree adjacency list
  int last = 0;

  void extend(char ch) {
    int c = ch - first;
    int p = last, q, clone, cur;
    if (N[p].next[c] != -1) {
      q = N[p].next[c];
      if (N[q].len == N[p].len + 1) { last = q; return; }
      clone = N.size();
      N.push_back(N[q]);
      N[clone].len = N[p].len + 1;
      N[clone].term = 0;
      N[clone].link = N[q].link;
      N[q].link = last = clone;
      while (p != -1 && N[p].next[c] == q) N[p].next[c] = clone, p = N[p].link;
      return;
    }
    cur = last = N.size();
    N.emplace_back(-1);
    N[cur].len = N[p].len + 1; N[cur].fpos = N[cur].len;
    while (p != -1 && N[p].next[c] == -1) N[p].next[c] = cur, p = N[p].link;
    if (p == -1) N[cur].link = 0;
    else {
      q = N[p].next[c];
      if (N[p].len + 1 == N[q].len) N[cur].link = q;
      else {
        clone = N.size();
        N.push_back(N[q]);
        N[clone].len = N[p].len + 1;
        N[clone].term = 0;
        while (p != -1 && N[p].next[c] == q) N[p].next[c] = clone, p = N[p].link;
        N[q].link = N[cur].link = clone;
      }
    }
  }
  SuffixAutomaton(const string &s) : N(1, -1) {
    for (char c : s) {
      extend(c);
      N[last].term = 1;
    }
    g.resize(N.size());
    for (int i = 1; i < (int)N.size(); i++) g[N[i].link].push_back(i);
  }
  // Computes the frequency of node[i]'s substrings
  long long get_occ(int i) {
    if (N[i].occ != -1) return N[i].occ;
    N[i].occ = N[i].term;
    for (int x : g[i]) N[i].occ += get_occ(x);
    return N[i].occ;
  }
};