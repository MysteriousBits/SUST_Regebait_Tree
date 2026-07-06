struct trienode {
  int size;
  bool endmark;
  vector<int> child;
  trienode(int sz) {
    size = 0;
    endmark = false;
    child.resize(sz, 0);
  }
};
struct trie {
  int sz;
  char fst;
  vector<trienode> nodes;
  // 26, 'a' for lowercase latin letters
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
      nodes[cur].size++;
      cur = nodes[cur].child[c - fst];
    }
    nodes[cur].endmark = true;
    nodes[cur].size++;
  }
  bool search(string& s) {
    int cur = 0;
    for (char c : s) {
      if (!nodes[cur].child[c - fst] || !nodes[cur].size) return false;
      cur = nodes[cur].child[c - fst];
    }
    return nodes[cur].endmark;
  }
  bool erase(string& s) {
    if (!search(s)) return false;
    int cur = 0;
    for (char c : s) {
      nodes[cur].size--;
      cur = nodes[cur].child[c - fst];
    }
    if (!--nodes[cur].size) nodes[cur].endmark = false;
    return true;
  }
};