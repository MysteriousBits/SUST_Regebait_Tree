auto qrsm = [](ll n) -> ll {
        ll ans = 0;
        ll po = 1;
        ll nm = n;
        while(n) {
            ll tm = n/10;
            ll rem = n%10;
            ll s1 = rem*(rem-1)/2;
            ll past = (nm%po)+1ll;
            ans += (tm*45ll)*po + (s1)*(po) + (rem * past);
            po *= 10;
            n /= 10;
        }
        return ans;
    };
    auto rsm = [&](ll l, ll r) -> ll{
        return qrsm(r) - qrsm(l-1);
    };