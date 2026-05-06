struct SqrtDecomp {
int n, sz;
    vector<ll> a;

    vector<map<int,int>> b;
    SqrtDecomp(int n, vi& arr) : n(n) {
        sz = sqrt(n) + 1;
        /*...*/
    }
    void upd(int i, ll v) {
        /*...*/
    }
    ll combine(ll s, ll elem, int v) { /*...*/ }
    ll combineBlock(ll s, map<int,int>& blk, int v) {
        /*...*/
    }
    ll query(int l, int r, int v) {
        ll s = 0;
        r--;
        if(l > r) {
            return 0;
        }
        int bl = l/sz, br = r/sz;
        if (bl == br) {
            for (int i = l; i <= r; i++) s = combine(s, a[i], v);
        } else {
            for (int i = l; i < (bl+1)*sz; i++) s = combine(s, a[i], v);
            for (int i = bl+1; i < br; i++) s = combineBlock(s, b[i], v);
            for (int i = br*sz; i <= r; i++) s = combine(s, a[i], v);
        }
        return s;
    }
};