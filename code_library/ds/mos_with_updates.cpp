struct mos_update {
    void add(int ind, int end) { ... }
    void del(int ind, int end) { ... }
    void apply(int pos, int val) { ... }
    int calc() { ... }

    int a[N];
    int L, R; // needed by apply

    void apply(int pos, int val) {
        if (L <= pos && pos < R) { del(pos, -1); a[pos] = val; add(pos, -1); }
        else                     { a[pos] = val; }
    }

    // Q[i] = {l, r, t}
    // U[i] = {pos, old_val, new_val}
    vector<int> mo(vector<vi> Q, vector<vi> U) {
        L = 0, R = 0; int T = 0;
        int blk = max(1, (int)pow(sz(Q), 0.666));
        vi s(sz(Q)), res = s;

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

            res[qi] = calc();
        }
        return res;
    }
}