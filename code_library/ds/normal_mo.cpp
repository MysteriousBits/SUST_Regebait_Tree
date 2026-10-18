struct MO{
   int n,q,B,res; struct query{ int l,r,id; };
   vector<query> Q; vector<int> ans,cnt;
   MO(int n, int q): n(n), q(q){
      res=0;
      B=sqrt(n)+1;
      ans.resize(q+1);
      cnt.resize(n+10);
   }
   void add_query(int l, int r, int id){ Q.push_back({l,r,id});}
   void add_left(int id,const vector<int>& a){}
   void add_right(int id,const vector<int>& a){}
   void rem_left(int id,const vector<int>& a){}
   void rem_right(int id,const vector<int>& a){}
   void get_ans(const vector<int>& a){
      sort(Q.begin(),Q.end(),[&](auto& x, auto& y){
         if(x.l/B == y.l/B){
            return ((x.l/B)&1) ? x.r>y.r : x.r<y.r;
         }
         return x.l/B < y.l/B;
      });
      int L=1,R=0;
      for(auto &[l,r,id]: Q){
         while(L>l)  add_left(--L,a);
         while(R<r)  add_right(++R,a);
         while(L<l)  rem_left(L++,a);
         while(R>r)  rem_right(R--,a);
         ans[id]=res;
      }
   }
};