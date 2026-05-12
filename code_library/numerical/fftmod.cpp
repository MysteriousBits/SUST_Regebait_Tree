template <ll M>
vector<ll> convMod(vector<ll>& a, vector<ll>& b) {
    if (a.empty() || b.empty()) return {};
    vector<ll> res(a.size() + b.size() - 1);
    int B = 32 - __builtin_clz((int)res.size()), n = 1 << B;
    int cut = (int)sqrt((double)M);
    vector<C> fa(n), fb(n), outs(n), outl(n);
    for (int i = 0; i < (int)a.size(); i++) fa[i] = C((int)a[i] / cut, (int)a[i] % cut);
    for (int i = 0; i < (int)b.size(); i++) fb[i] = C((int)b[i] / cut, (int)b[i] % cut);
    fft(fa); fft(fb);
    for (int i = 0; i < n; i++) {
        int j = -i & (n - 1);
        outl[j] = (fa[i] + conj(fa[j])) * fb[i] / (2.0 * n);
        outs[j] = (fa[i] - conj(fa[j])) * fb[i] / (2.0 * n) / C(0, 1);
    }
    fft(outl); fft(outs);
    for (int i = 0; i < (int)res.size(); i++) {
        ll av = llround(real(outl[i]));
        ll bv = llround(imag(outl[i])) + llround(real(outs[i]));
        ll cv = llround(imag(outs[i]));
        res[i] = ((av % M * cut + bv) % M * cut + cv) % M;
    }
    return res;
}