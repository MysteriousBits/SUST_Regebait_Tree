#include <bits/stdc++.h>
using namespace std;
// Template
// ==============================================
// pbds
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// template<typename T>
// using ordered_set =  tree<T, null_type, less<T>, rb_tree_tag,
// tree_order_statistics_node_update>;
// Debugging
#ifdef LOCAL
#include "debug.h"
#else
#define debug(...)
#define see(x)
#endif
typedef long long ll;
typedef vector<int> VI;
typedef vector<long long> VLL;
typedef vector<bool> VB;
typedef vector<vector<int>> VVI;
typedef pair<int, int> PI;
typedef pair<ll, ll> PLL;
typedef vector<pair<int, int>> VPI;
#define pb push_back
#define ff first
#define ss second
#define mp make_pair
#define all(a) a.begin(), a.end()
#define revall(a) a.rbegin(), a.rend()
#define loop(i, s, e) for (int i = s; i < e; ++i)
#define inp(v)
for (auto& x : v) cin >> x
#define outp(v, st)
for (int i = st, n = v.size(); i < n; ++i) cout << v[i] << " \n"[i == n - 1]
#define nl "\n"
#define yep cout << "YES\n"
#define nope cout << "NO\n"
#define INF (int)1e9
#define INFL (ll)1e18
#define EPS 1e-9
#define MOD 998244353
// #define MOD 1000000007
#define MAXN 2002
// =============================================
void solve(int tc) {}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t = 1;
  // cin >> t;
  for (int i = 1; i <= t; ++i) solve(i);
#ifdef LOCAL
  cerr << "Execution time: " << 1000.f * clock() / CLOCKS_PER_SEC << " ms."
       << nl;
#endif
  return 0;
}