struct AhoCorasick {
  static const int alpha = 26; char first = 'a'; // change this
  struct Node {
    int link = 0, out = 0, cnt = 0, nxt[alpha]{};
    vector<int> end;
  };
  vector<Node> trie;
  AhoCorasick(vector<string>& pat) {
    trie.emplace_back();
    for (int i = 0; i < (int)pat.size(); i++) insert(pat[i], i);
    queue<int> q; q.push(0);
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int i = 0; i < alpha; i++) if (trie[u].nxt[i]) {
        int v = trie[u].nxt[i], p = trie[u].link;
        while (p && !trie[p].nxt[i]) p = trie[p].link;
        if (trie[p].nxt[i] != v) trie[v].link = trie[p].nxt[i];
        trie[v].out = !trie[trie[v].link].end.empty() ? trie[v].link : trie[trie[v].link].out;
        trie[v].cnt = trie[v].end.size() + trie[trie[v].out].cnt;
        q.push(v);
      }
    }
  }
  void process(int pat_id, int end_pos) {} // process match, end_pos non-decreasing
  void insert(string& s, int id) {
    int u = 0;
    for (char c : s) {
      if (!trie[u].nxt[c - first]) {
        trie[u].nxt[c - first] = trie.size();
        trie.emplace_back();
      }
      u = trie[u].nxt[c - first];
    }
    trie[u].end.push_back(id);
  }
  void find(string& s) {
    int u = 0;
    for (int i = 0; i < (int)s.size(); i++) {
      while (u && !trie[u].nxt[s[i] - first]) u = trie[u].link;
      u = trie[u].nxt[s[i] - first];
      for (int id : trie[u].end) process(id, i);
      for (int o = trie[u].out; o; o = trie[o].out)
        for (int id : trie[o].end) process(id, i);
    }
  }
  vector<int> count(string& s) { // total pattern matches ending at each index
    int u = 0; vector<int> cnt(s.size());
    for (int i = 0; i < (int)s.size(); i++) {
      while (u && !trie[u].nxt[s[i] - first]) u = trie[u].link;
      u = trie[u].nxt[s[i] - first];
      cnt[i] = trie[u].cnt;
    }
    return cnt;
  }
};