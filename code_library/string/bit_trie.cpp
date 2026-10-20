#define MAXN 4000005 // > 31 * N
int trie[MAXN][2], tsz[MAXN], nodes = 0, bitsz = 30;

void insert(int x) {
  int cur = 0;
  for (int i = bitsz; i >= 0; --i) {
    int ch = (x >> i) & 1;
    if (!trie[cur][ch]) trie[cur][ch] = ++nodes;
    tsz[cur]++;
    cur = trie[cur][ch];
  }
  tsz[cur]++;
}
void erase(int x) {
  int cur = 0;
  for (int i = bitsz; i >= 0; --i) {
    int ch = (x >> i) & 1;
    if (!tsz[cur] || !trie[cur][ch]) return;
    tsz[cur]--;
    cur = trie[cur][ch];
  }
  tsz[cur]--;
}
int get_kth(int x, int k = 1) {
  int cur = 0, ans = 0;
  for (int i = bitsz; i >= 0; --i) {
    int ch = (x >> i) & 1;
    ch = 1 - ch;  // remove for kth_min()
    if (!trie[cur][ch]) ch = 1 - ch;
    else if (tsz[trie[cur][ch]] < k)
      k -= tsz[trie[cur][ch]], ch = 1 - ch;
    cur = trie[cur][ch];
    ans |= ch << i;
  }
  return ans ^ x;
}
void dfs(int u = 0, int depth = 0) {
  // custom logic
  if (trie[u][0]) dfs(trie[u][0], depth + 1);
  if (trie[u][1]) dfs(trie[u][1], depth + 1);
}
void deleteall(int root) {
  if (trie[root][0]) deleteall(trie[root][0]);
  if (trie[root][1]) deleteall(trie[root][1]);
  trie[root][0] = trie[root][1] = 0;
  tsz[root] = 0;
}
void cleanup() {
  nodes = 0;
  deleteall(0);
}