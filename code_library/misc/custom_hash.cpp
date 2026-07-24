struct custom_hash{
static uint64_t sm64(uint64_t x){x+=0x9e3779b97f4a7c15; x=(x^(x>>30))*0xbf58476d1ce4e5b9; x=(x^(x>>27))*0x94d049bb133111eb; return x^(x>>31);}
size_t operator()(uint64_t x) const{static const uint64_t R=chrono::steady_clock::now().time_since_epoch().count(); return sm64(x+R);}
template<class T1,class T2> size_t operator()(const pair<T1,T2>&p) const{size_t h1=(*this)((uint64_t)p.first),h2=(*this)((uint64_t)p.second); return h1^(h2+0x9e3779b9+(h1<<6)+(h1>>2));}
template<class...Ts> size_t operator()(const tuple<Ts...>&t) const{size_t s=0; apply([&](const auto&...e){((s^=(*this)((uint64_t)e)+0x9e3779b9+(s<<6)+(s>>2)),...);},t); return s;}
template<class T> size_t operator()(const vector<T>&v) const{size_t s=v.size(); for(auto&x:v) s^=(*this)((uint64_t)x)+0x9e3779b9+(s<<6)+(s>>2); return s;}
};
