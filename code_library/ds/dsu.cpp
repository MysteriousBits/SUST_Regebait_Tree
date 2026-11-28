struct DSU {
   vector<int> par,sz;
   DSU(){}
   DSU(int n){
      init(n);
   }
   void init(int n){
      par.resize(n);
      iota(par.begin(),par.end(),0);
      sz.assign(n,1);
   }
   int find(int v){
      while(v!=par[v]){
         v=par[v]=par[par[v]]; 
      }
      return v;
   }
   bool merge(int a,int b){
      a=find(a);
      b=find(b);
      if(a==b) return false;
      if(sz[a]<sz[b]) swap(a, b);
      par[b]=a;
      sz[a]+=sz[b];
      return true;
   }
};
