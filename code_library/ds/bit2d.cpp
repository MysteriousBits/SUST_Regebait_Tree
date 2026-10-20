template<typename T>
struct BIT2D{
  int n,m; vector<vector<T>> t;
  BIT2D(int n,int m):n(n),m(m),t(n+2,vector<T>(m+2,0)){}
  void update(int x,int y,T val){
    for(int i=x;i<=n;i+=(i&-i))for(int j=y;j<=m;j+=(j&-j))t[i][j]+=val;
  }
  void range_update(int x1,int y1,int x2,int y2,T val){
    update(x1,y1,val);
    update(x1,y2+1,-val);
    update(x2+1,y1,-val);
    update(x2+1,y2+1,val);
  }
  T query(int x,int y)const{
    T sum=0;
    for(int i=x;i>0;i-=(i&-i))for(int j=y;j>0;j-=(j&-j))sum+=t[i][j];
    return sum;
  }
  T query(int x1,int y1,int x2,int y2)const{
    return query(x2,y2)-query(x1-1,y2)-query(x2,y1-1)+query(x1-1,y1-1);
  }
  void reset(){
    for(int i=0;i<=n;++i)fill(t[i].begin(),t[i].end(),0);
  }
};