
#define MAXN 4000005
int trie[MAXN][2], triesz[MAXN], nodes = 0, bitsz = 30;
void insert(int x) {
  int cur = 0;
  for (int i = bitsz; i >= 0; --i) {
    int child = x & (1 << i) ? 1 : 0;
    if (!trie[cur][child]) trie[cur][child] = ++nodes;
    triesz[cur]++;
    cur = trie[cur][child];
  }
  triesz[cur]++;
}
void erase(int x) {
  int cur = 0;
  for (int i = bitsz; i >= 0; --i) {
    int child = x & (1 << i) ? 1 : 0;
    if (!triesz[cur] || !trie[cur][child]) return;
    triesz[cur]--;
    cur = trie[cur][child];
  }
  triesz[cur]--;
}
// max xor with x
int get_max(int x) {
  int cur = 0, ans = 0;
  for (int i = bitsz; i >= 0; --i) {
    int child = x & (1 << i) ? 1 : 0;
    child = 1 - child;  // remove for get_min()
    if (!trie[cur][child] || !triesz[trie[cur][child]]) child = 1 - child;
    cur = trie[cur][child];
    ans |= child << i;
  }
  return ans ^ x;
}
void deleteall(int root) {
  if (trie[root][0]) deleteall(trie[root][0]);
  if (trie[root][1]) deleteall(trie[root][1]);
  triesz[root] = 0;
}
void cleanup() {
  nodes = 0;
  deleteall(0);
}