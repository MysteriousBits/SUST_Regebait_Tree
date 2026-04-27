struct trienode {
  bool endmark;
  vector<int> child;
  trienode(int sz) {
    endmark = false;
    child.resize(sz, 0);
  }
};
struct trie {
  int sz;
  char fst;
  vector<trienode> nodes;
  trie(int alpha_sz, char alpha_start) {
    sz = alpha_sz;
    fst = alpha_start;
    // root at idx 0
    nodes.pb(trienode(sz));
  }
  void insert(string& s) {
    int cur = 0;
    for (char c : s) {
      if (!nodes[cur].child[c - fst]) {
        nodes[cur].child[c - fst] = nodes.size();
        nodes.pb(trienode(sz));
      }
      cur = nodes[cur].child[c - fst];
    }
    nodes[cur].endmark = true;
  }
  bool search(string& s) {
    int cur = 0;
    for (char c : s) {
      if (!nodes[cur].child[c - fst]) return false;
      cur = nodes[cur].child[c - fst];
    }
    return nodes[cur].endmark;
  }
  bool erase(string& s) {
    int cur = 0;
    for (char c : s) {
      if (!nodes[cur].child[c - fst]) return false;
      cur = nodes[cur].child[c - fst];
    }
    if (!nodes[cur].endmark) return false;
    nodes[cur].endmark = false;
    return true;
  }
};