vector<int> val, comp, z;
int Time, ncomps;
vector<vector<int>> sccs;

int dfs(int j, vector<vector<int>>& g) {
    int low = val[j] = ++Time, x; z.push_back(j);
    for (int e : g[j]) if (comp[e] < 0)
        low = min(low, val[e] ?: dfs(e, g));

    if (low == val[j]) {
        sccs.push_back({});
        do {
            x = z.back(); z.pop_back();
            comp[x] = ncomps;
            sccs.back().push_back(x);
        } while (x != j);
        ncomps++;
    }
    return val[j] = low;
}

void get_sccs(vector<vector<int>>& g) {
    int n = g.size();
    val.assign(n, 0); comp.assign(n, -1);
    z.clear(); sccs.clear();
    Time = ncomps = 0;
    for (int i = 0; i < n; i++) if (comp[i] < 0) dfs(i, g);
}