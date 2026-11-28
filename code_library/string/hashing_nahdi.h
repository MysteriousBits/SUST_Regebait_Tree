const ll a1 = 911382, b1 = 1e9 + 7;
const ll a2 = 972663, b2 = 1e9 + 9;
ll p1[maxN], p2[maxN];

void pre() {
    p1[0] = p2[0] = 1;
    for (int i = 1; i < maxN; i++) {
        p1[i] = (p1[i - 1] * a1) % b1;
        p2[i] = (p2[i - 1] * a2) % b2;
    }
}

struct Hash {
    vector<ll> h1, h2;
    int n;
    string s;
    Hash(string s) : s(s), n(s.size()) {
        h1.resize(n + 1, 0); h2.resize(n + 1, 0);
        for (int i = 0; i < n; i++) {
            h1[i + 1] = (h1[i] * a1 + s[i]) % b1;
            h2[i + 1] = (h2[i] * a2 + s[i]) % b2;
        }
    }
    pll get(int l, int r) { // [l, r] 0-indexed
        ll r1 = (h1[r + 1] - h1[l] * p1[r - l + 1]) % b1;
        ll r2 = (h2[r + 1] - h2[l] * p2[r - l + 1]) % b2;
        return {r1 < 0 ? r1 + b1 : r1, r2 < 0 ? r2 + b2 : r2};
    }
    int count(string& pat) {
        int m = pat.size(), cnt = 0;
        if (m > n) return 0;
        Hash target(pat);
        return count(target, 0, target.n-1);
    }
    int search(string& pat) {
        int m = pat.size();
        if (m > n) return -1;
        Hash target(pat);
        return search(target, 0, target.n-1);
    }
    int count(Hash& h, int l, int r) {
        int m = r - l + 1, cnt = 0;
        if (m > n) return 0;
        pll target = h.get(l, r);
        for (int i = 0; i <= n - m; i++)
            if (get(i, i + m - 1) == target) cnt++;
        return cnt;
    }
    int search(Hash& h, int l, int r) {
        int m = r - l + 1;
        if (m > n) return -1;
        pll target = h.get(l, r);
        for (int i = 0; i <= n - m; i++)
            if (get(i, i + m - 1) == target) return i;
        return -1;
    }
    int lcp(int i, int j) { // LCP of suffix i and suffix j
       int lo = 0, hi = min(n - i, n - j);
       while (lo < hi) {
           int mid = (lo + hi + 1) / 2;
           if (get(i, i+mid-1) == get(j, j+mid-1)) lo = mid;
           else hi = mid - 1;
       }
       return lo;
   }
   // lcp between this[i,...] amd b[j,...]
   int lcp(Hash& b, int i, int j) {
        int lo = 0, hi = min(n - i, b.n - j);
        while (lo < hi) {
            int mid = (lo + hi + 1) / 2;
            if (get(i, i+mid-1) == b.get(j, j+mid-1)) lo = mid;
            else hi = mid - 1;
        }
        return lo;
    }
    // LCS of s[..i] and s[..j]
    int lcs(int i, int j) {
        int lo = 0, hi = min(i + 1, j + 1);
        while (lo < hi) {
            int mid = (lo + hi + 1) / 2;
            if (get(i-mid+1, i) == get(j-mid+1, j)) lo = mid;
            else hi = mid - 1;
        }
        return lo;
    }

    // Cross-string LCS: LCS of this[...i] and b[...j]
    int lcs(Hash& b, int i, int j) {
        int lo = 0, hi = min(i + 1, j + 1);
        while (lo < hi) {
            int mid = (lo + hi + 1) / 2;
            if (get(i-mid+1, i) == b.get(j-mid+1, j)) lo = mid;
            else hi = mid - 1;
        }
        return lo;
    }
    // if s+s+s... (1 or more times) = t -> true
    bool repeat(string& s_in) {
        int m = s_in.size();
        if (m == 0 || n % m != 0 || n == 0) return false;
        Hash temp(s_in);
        if (get(0, m - 1) != temp.get(0, m - 1)) return false; 
        if (n > m && get(0, n - m - 1) != get(m, n - 1)) return false; 
        return true;
    }
};