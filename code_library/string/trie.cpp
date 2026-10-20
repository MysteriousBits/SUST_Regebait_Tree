#define MAXN 4000005 // > total length of all strings combined
int trie[MAXN][26], tsz[MAXN], nodes = 0;
bool end[MAXN];

void insert(const string& s, char fst = 'a') {
  int cur = 0;
  for (char c : s) {
    int ch = c - fst;
    if (!trie[cur][ch]) trie[cur][ch] = ++nodes;
    tsz[cur]++;
    cur = trie[cur][ch];
  }
  tsz[cur]++;
  end[cur] = true;
}
bool search(const string& s, char fst = 'a') {
  int cur = 0;
  for (char c : s) {
    int ch = c - fst;
    if (!trie[cur][ch] || !tsz[cur]) return false;
    cur = trie[cur][ch];
  }
  return end[cur] && tsz[cur] > 0;
}
bool erase(const string& s, char fst = 'a') {
  if (!search(s, fst)) return false;
  int cur = 0;
  for (char c : s) {
    int ch = c - fst;
    tsz[cur]--;
    cur = trie[cur][ch];
  }
  tsz[cur]--;
  if (!tsz[cur]) end[cur] = false;
  return true;
}
void dfs(int u = 0, int depth = 0) {
  // custom logic
  for (int i = 0; i < 26; ++i) {
    if (trie[u][i]) {
      dfs(trie[u][i], depth + 1);
    }
  }
}
void deleteall(int root = 0) {
  for (int i = 0; i < 26; ++i) {
    if (trie[root][i]) {
      deleteall(trie[root][i]);
      trie[root][i] = 0;
    }
  }
  tsz[root] = 0;
  end[root] = false;
}
void cleanup() {
  nodes = 0;
  deleteall(0);
}