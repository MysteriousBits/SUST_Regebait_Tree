void fft(vector<C>& a) {
    int n = a.size(), L = 31 - __builtin_clz(n);
    static vector<complex<long double>> R(2, 1);
    static vector<C> rt(2, 1);
    static int kBuilt = 2;
    for (; kBuilt < n; kBuilt *= 2) {
        R.resize(2 * kBuilt);
        rt.resize(2 * kBuilt);
        auto x = polar(1.0L, acos(-1.0L) / kBuilt);
        for (int i = kBuilt; i < 2 * kBuilt; i++)
            rt[i] = R[i] = (i & 1) ? R[i / 2] * x : R[i / 2];
    }

    vector<int> rev(n);
    for (int i = 0; i < n; i++) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    for (int i = 0; i < n; i++) if (i < rev[i]) swap(a[i], a[rev[i]]);

    for (int k = 1; k < n; k *= 2)
        for (int i = 0; i < n; i += 2 * k)
            for (int j = 0; j < k; j++) {
                // Hand-rolled complex multiply (~25% faster than rt[j+k]*a[i+j+k])
                auto x = (double*)&rt[j + k];
                auto y = (double*)&a[i + j + k];
                C z(x[0] * y[0] - x[1] * y[1],
                    x[0] * y[1] + x[1] * y[0]);
                a[i + j + k] = a[i + j] - z;
                a[i + j]    += z;
            }
}

vd conv(const vd& a, const vd& b) {
    if (a.empty() || b.empty()) return {};
    vd res(a.size() + b.size() - 1);
    int L = 32 - __builtin_clz((int)res.size()), n = 1 << L;
    vector<C> in(n), out(n);
    copy(a.begin(), a.end(), in.begin());
    for (int i = 0; i < (int)b.size(); i++) in[i].imag(b[i]);
    fft(in);
    for (C& x : in) x *= x;
    for (int i = 0; i < n; i++) out[i] = in[-i & (n - 1)] - conj(in[i]);
    fft(out);
    for (int i = 0; i < (int)res.size(); i++) res[i] = imag(out[i]) / (4 * n);
    return res;
}