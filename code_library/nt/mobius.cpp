int mob[N];
// Precomputes Mobius function μ(i) for all 1 <= i < N.
void mobius() {
  mob[1] = 1;
  for (int i = 2; i < N; i++){
    mob[i]--;
    for (int j = i + i; j < N; j += i) mob[j] -= mob[i];
  }
}
bool vis[N];
vector<int> d[N];
int mul[N];
// Inserts (k=1) or removes (k=-1) x by updating divisor frequencies.
void add(int x, int k) {
  for (auto y: d[x]) mul[y] += k;
}
// Returns the count of active set elements coprime to x.
int query(int x) {
  int ans = 0;
  for (auto y: d[x]) ans += mul[y] * mob[y];
  return ans;
}