long long sweep_line_x;
struct Segment{long long a,b,x,y;int idx;};
struct Point{long long x,y;int segment_idx;};
int sign(long long x){return x==0?0:(x<0?-1:1);}
double coordinate(const Segment&s){
    if(s.a==s.x)return s.b;
    return s.b+(double)(s.y-s.b)*(sweep_line_x-s.a)/(s.x-s.a);
}
bool operator<(const Segment&u,const Segment&v){
    if(u.idx==v.idx)return false;
    return coordinate(u)<coordinate(v);
}
bool operator==(const Segment&u,const Segment&v){return u.idx==v.idx;}
long long orientation(Point a,Point b,Point c){
    return (b.x-a.x)*(c.y-a.y)-(c.x-a.x)*(b.y-a.y);
}
bool intersect(const Segment&a,const Segment&b){
    Point p1{a.a,a.b,0},q1{a.x,a.y,0},p2{b.a,b.b,0},q2{b.x,b.y,0};
    long long o1=orientation(p1,q1,p2),o2=orientation(p1,q1,q2);
    long long o3=orientation(p2,q2,p1),o4=orientation(p2,q2,q1);
    return sign(o1)*sign(o2)<=0&&sign(o3)*sign(o4)<=0;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;cin>>n;
    vector<Segment>segments(n);
    vector<Point>events;
    for(int i=0;i<n;i++){
        cin>>segments[i].a>>segments[i].b>>segments[i].x>>segments[i].y;
        segments[i].idx=i;
        events.push_back({segments[i].a,segments[i].b,i});
        events.push_back({segments[i].x,segments[i].y,i});
    }
    sort(events.begin(),events.end(),[](const Point&p,const Point&q){
        if(p.x!=q.x)return p.x<q.x;
        return p.y<q.y;
    });
    set<Segment>active;
    int first=-1,second=-1;
    for(auto&e:events){
        sweep_line_x=e.x;
        int id=e.segment_idx;
        auto it=active.find(segments[id]);
        if(it!=active.end()){
            auto nxt=next(it);
            if(it!=active.begin()&&nxt!=active.end()){
                auto prv=prev(it);
                if(intersect(segments[prv->idx],segments[nxt->idx])){
                    first=prv->idx;second=nxt->idx;break;
                }
            }
            active.erase(it);
        }else{
            it=active.lower_bound(segments[id]);
            if(it!=active.end()&&intersect(segments[id],*it)){
                first=id;second=it->idx;break;
            }
            if(it!=active.begin()){
                auto prv=prev(it);
                if(intersect(segments[id],*prv)){
                    first=id;second=prv->idx;break;
                }
            }
            active.insert(segments[id]);
        }
    }
    if(first>second)swap(first,second);
    int cnt=0;
    for(int i=0;i<n;i++)
        if(i!=second&&intersect(segments[i],segments[second]))cnt++;
    cout<<(cnt>1?second+1:first+1);
}