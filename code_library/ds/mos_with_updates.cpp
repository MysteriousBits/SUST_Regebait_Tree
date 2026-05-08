/// @note: Store query indices as [l, r). DON'T FORGET TO MAKE R EXCLUSIVE
struct mos_update {
    ll a[100005];
    int L, R; // needed by apply
    ll ans;
    mos_update() { /* ... */ }
    void add(int ind, int end) { /* ... */ }
    void del(int ind, int end) { /* ... */ }

    void apply(int pos, int val) {
        if (L <= pos && pos < R) { del(pos, -1); a[pos] = val; add(pos, -1); }
        else                     { a[pos] = val; }
    }
    // Q[i] = {l, r, t}
    // U[i] = {pos, old_val, new_val}
    vector<ll> mo(vector<vector<int>>& Q, vector<vector<int>>& U, int n) {
        L = 0, R = 0; int T = 0;
        ans = 0;
        int blk = max(1, (int)pow(Q.size(), 0.666));
        vll s(Q.size()), res(Q.size());

        iota(all(s), 0);
        sort(all(s), [&](int i, int j) {
            int li = Q[i][0]/blk, lj = Q[j][0]/blk;
            if (li != lj) return li < lj;
            int ri = Q[i][1]/blk, rj = Q[j][1]/blk;
            if (ri != rj) return (li & 1) ? ri < rj : ri > rj;
            return (ri & 1) ? Q[i][2] < Q[j][2] : Q[i][2] > Q[j][2];
        });

        for (int qi : s) {
            int ql = Q[qi][0], qr = Q[qi][1], qt = Q[qi][2];

            while (T < qt) { auto& u = U[T++]; apply(u[0], u[2]); }
            while (T > qt) { auto& u = U[--T]; apply(u[0], u[1]); }

            while (L > ql) add(--L, 0);
            while (R < qr) add(R++, 1);
            while (L < ql) del(L++, 0);
            while (R > qr) del(--R, 1);
            res[qi] = ans;
        }
        return res;
    }
};