//USAGE

// 1.FOR NODES
HLD<false> hld(n, adj);
for (int u = 1; u <= n; u++) {
    // node[u] represents the scanned value
    a[hld.pos[u]] = node[u]; 
}
hld.st.build(1, 1, n);

// 2. FOR EDGES
HLD<true> hld(n, adj); // NOTE: adj is normal vector<vector<int>>
for (auto &e : edges) {
    int u = e.u, v = e.v, w = e.w;
    if (hld.dep[u] < hld.dep[v]) swap(u, v); 
    a[hld.pos[u]] = w;
}
hld.st.build(1, 1, n);

template<bool EDGES> struct HLD {
    int n, tim;
    vector<int> par, sz, dep, root, pos;
    vector<vector<int>> adj;
    ST st; // Embedded Segment Tree
    
    HLD(int _n, vector<vector<int>>& _adj) : n(_n), par(_n+1), sz(_n+1, 1), 
                 dep(_n+1), root(_n+1), pos(_n+1), adj(_adj) {
        tim = 1;
        dfs_sz(1, 0, 0);
        dfs_hld(1, 1);
    }

    void dfs_sz(int u, int p, int d) {
        par[u] = p; dep[u] = d; sz[u] = 1;
        for (int i = 0; i < adj[u].size(); i++) {
            if (adj[u][i] == p) {
                adj[u].erase(adj[u].begin() + i);
                break;
            }
        }
        int heavy = -1, max_sz = -1;
        for (int &v : adj[u]) {
            dfs_sz(v, u, d + 1);
            sz[u] += sz[v];
            if (sz[v] > max_sz) {
                max_sz = sz[v];
                heavy = v;
            }
        }
        if (heavy != -1) {
            for (int i = 0; i < adj[u].size(); i++) {
                if (adj[u][i] == heavy) {
                    swap(adj[u][i], adj[u][0]);
                    break;
                }
            }
        }
    }

    void dfs_hld(int u, int r) {
        root[u] = r; pos[u] = tim++;
        for (int v : adj[u]) {
            dfs_hld(v, (v == adj[u][0] ? r : v));
        }
    }

    int getLCA(int u, int v) {
        while (root[u] != root[v]) {
            if (dep[root[u]] > dep[root[v]]) u = par[root[u]];
            else v = par[root[v]];
        }
        return dep[u] < dep[v] ? u : v;
    }

    // update path(u,v) with value val
    void updatePath(int u, int v, long long val) {
        while (root[u] != root[v]) {
            if (dep[root[u]] > dep[root[v]]) swap(u, v);
            st.upd(1, 1, n, pos[root[v]], pos[v], val);
            v = par[root[v]];
        }
        if (dep[u] > dep[v]) swap(u, v);
        if (!EDGES || pos[u] < pos[v]) {
            st.upd(1, 1, n, pos[u] + (EDGES ? 1 : 0), pos[v], val);
        }
    }

    // query path(u,v)
    long long queryPath(int u, int v) {
        long long resL = 0, resR = 0; // 0 is identity for sum
        while (root[u] != root[v]) {
            if (dep[root[u]] > dep[root[v]]) {
                // Climbing up from u
                resL = st.combine(resL, st.query(1, 1, n, pos[root[u]], pos[u]));
                u = par[root[u]];
            } else {
                // Climbing up from v
                resR = st.combine(st.query(1, 1, n, pos[root[v]], pos[v]), resR);
                v = par[root[v]];
            }
        }
        // Merge the final heavy chain
        if (dep[u] > dep[v]) {
            resL = st.combine(resL, st.query(1, 1, n, pos[v] + (EDGES ? 1 : 0), pos[u]));
        } else {
            resR = st.combine(st.query(1, 1, n, pos[u] + (EDGES ? 1 : 0), pos[v]), resR);
        }
        
        return st.combine(resL, resR); 
    }
    void updateSubtree(int u, long long val) {
        if (EDGES && sz[u] == 1) return; 
        st.upd(1, 1, n, pos[u] + (EDGES ? 1 : 0), pos[u] + sz[u] - 1, val);
    }
    long long querySubtree(int u) {
        if (EDGES && sz[u] == 1) return 0;
        return st.query(1, 1, n, pos[u] + (EDGES ? 1 : 0), pos[u] + sz[u] - 1);
    }
};