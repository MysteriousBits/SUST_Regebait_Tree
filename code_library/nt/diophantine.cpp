// Solves a*x + b*y = c
bool find_any_solution(ll a,ll b,ll c,ll &x0,ll &y0,ll &g){
    if(a==0&&b==0){
        if(c) return false;
        x0=y0=g=0; return true;
    }
    g=extended_gcd(abs(a),abs(b),x0,y0);
    if(c%g!=0) return false;
    x0*=c/g; y0*=c/g;
    if(a<0) x0*=-1;
    if(b<0) y0*=-1;
    return true;
}

// Shift solution by cnt
void shift_solution(ll &x,ll &y,ll a,ll b,ll cnt){
    x+=cnt*b; y-=cnt*a;
}
pair<ll, vector<pair<ll, ll>>> find_all_solutions(ll a,ll b,ll c,
                      ll minx,ll maxx,ll miny,ll maxy, bool solves){
    ll x,y,g;
    if(!find_any_solution(a,b,c,x,y,g)) return {0, {}};
    if(a==0&&b==0){
        assert(c==0);
        ll cnt = 1LL*(maxx-minx+1)*(maxy-miny+1);
        vector<pair<ll, ll>> res;
        if(solves){
            for(ll cur_x=minx; cur_x<=maxx; ++cur_x){
                for(ll cur_y=miny; cur_y<=maxy; ++cur_y){
                    res.push_back({cur_x, cur_y});
                }
            }
        }
        return {cnt, res};
    }
    if(a==0){
        ll cnt = (maxx-minx+1)*(miny<=c/b&&c/b<=maxy);
        vector<pair<ll, ll>> res;
        if(solves && cnt > 0){
            ll cur_y = c/b;
            for(ll cur_x=minx; cur_x<=maxx; ++cur_x){
                res.push_back({cur_x, cur_y});
            }
        }
        return {cnt, res};
    }
    if(b==0){
        ll cnt = (maxy-miny+1)*(minx<=c/a&&c/a<=maxx);
        vector<pair<ll, ll>> res;
        if(solves && cnt > 0){
            ll cur_x = c/a;
            for(ll cur_y=miny; cur_y<=maxy; ++cur_y){
                res.push_back({cur_x, cur_y});
            }
        }
        return {cnt, res};
    }

    ll orig_a = a, orig_b = b;
    a/=g; b/=g;
    ll sign_a=a>0?1:-1, sign_b=b>0?1:-1;

    shift_solution(x,y,a,b,(minx-x)/b);
    if(x<minx) shift_solution(x,y,a,b,sign_b);
    if(x>maxx) return {0, {}};
    ll lx1=x;

    shift_solution(x,y,a,b,(maxx-x)/b);
    if(x>maxx) shift_solution(x,y,a,b,-sign_b);
    ll rx1=x;

    shift_solution(x,y,a,b,-(miny-y)/a);
    if(y<miny) shift_solution(x,y,a,b,-sign_a);
    if(y>maxy) return {0, {}};
    ll lx2=x;

    shift_solution(x,y,a,b,-(maxy-y)/a);
    if(y>maxy) shift_solution(x,y,a,b,sign_a);
    ll rx2=x;

    if(lx2>rx2) swap(lx2,rx2);
    ll lx=max(lx1,lx2), rx=min(rx1,rx2);
    if(lx>rx) return {0, {}};
    
    ll cnt = (rx-lx)/abs(b)+1;
    vector<pair<ll, ll>> res;
    if(solves){
        for(ll cur_x=lx; cur_x<=rx; cur_x+=abs(b)){
            res.push_back({cur_x, (c-orig_a*cur_x)/orig_b});
        }
    }
    return {cnt, res};
}