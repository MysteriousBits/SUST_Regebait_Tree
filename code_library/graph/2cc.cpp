struct TECC{
  using Edge=array<int,2>;
  int n,cnt_comp;
  vector<vector<int>> G,T; vector<bool> vis;
  vector<int> tin,low,comp; vector<Edge> bridges;
  void low_dfs(int u, int par, int& cur){
    vis[u]=true; tin[u]=cur++; low[u]=n+1;
    bool usedPar=false;
    for(auto v: G[u]){
      if(vis[v]){
        if(v!=par || usedPar){
          low[u]=min(low[u],tin[v]);
        }else{
          usedPar=true;
        }
        continue;
      }
      low_dfs(v,u,cur);
      low[u]=min(low[u],low[v]);
    }
  }
  void build_dfs(int u, int cid){
    comp[u]=cid;
    for(auto v: G[u]){
      if(comp[v]!=-1)      continue;
      if(tin[u]<low[v]){
        bridges.push_back({u,v});
        cnt_comp++;
        build_dfs(v,cnt_comp);
      }else{
        build_dfs(v,cid);
      }
    }
  }
  TECC(int _n,const vector<vector<int>>& g){
    n=_n; G=g; cnt_comp=1;
    tin.resize(n+1);
    low.resize(n+1);
    vis.assign(n+1,false);
    comp.assign(n+1,-1);
    int cur=1;
    for(int i=1;i<=n;i++){
      if(vis[i])     continue;
      low_dfs(i,-1,cur);
      build_dfs(i,cnt_comp);
      cnt_comp++;
    }
  }
  void build_tree(){
    T.assign(cnt_comp,{});
    for(auto &e: bridges){
      int u=comp[e[0]],v=comp[e[1]];
      T[u].push_back(v);
      T[v].push_back(u);
    }
  }
};
