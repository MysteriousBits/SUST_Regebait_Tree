struct BI{
  vector<ll>a; ll g=1e9;
  BI(ll v=0){
    if(!v) a={0};
    while(v) a.push_back(v%g), v/=g;}
  void z() { while(a.size()>1 && !a.back()) a.pop_back();}
  BI operator+(const BI&v)const{
    BI r; r.a.clear(); ll c=0;
    for(size_t i=0; i < max(a.size(),v.a.size()) || c ; i++){
      ll s = c + (i<a.size() ? a[i]:0) + (i<v.a.size() ? v.a[i]:0);
      c=s/g;r.a.push_back(s%g); }
    r.z();return r;}
  BI operator*(const BI&v)const{
    BI r;r.a.assign(a.size()+v.a.size(),0);
    for(size_t i=0;i<a.size();i++){
      ll c=0;
      for(size_t j=0;j<v.a.size()||c;j++){
        ll x=r.a[i+j]+a[i]*(j<v.a.size()?v.a[j]:0)+c;
        c=x/g;r.a[i+j]=x%g;}  }
    r.z();return r;}
  BI operator/(ll v)const{
    BI r;r.a.clear();ll m=0;
    for(int i=(int)a.size()-1;i>=0;i--){
      ll x=a[i]+m*g;
      r.a.push_back(x/v);m=x%v;}
    reverse(r.a.begin(),r.a.end());r.z();return r;}
  void print()const{
    cout<<(a.empty()?0:a.back());
    for(int i=(int)a.size()-2;i>=0;i--)
      cout<<setw(9)<<setfill('0')<<a[i];
    cout<<'\n';
  }
};