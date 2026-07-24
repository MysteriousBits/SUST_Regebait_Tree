// Primitive root modulo p (p must be prime) g is primitive if g^(phi/p_i) != 1 for all prime factors p_i of phi 
int PrimitiveRoot(int p){
    vector<int>fact;
    int phi=p-1,n=phi;
    for(int i=2;i*i<=n;i++){
        if(n%i==0){
            fact.push_back(i);
            while(n%i==0)n/=i;
        }
    }
    if(n>1)fact.push_back(n);
    for(int g=2;g<=p;g++){
        bool ok=true;
        for(int f:fact)
            ok&=BigMod(g,phi/f,p)!=1;
        if(ok)return g;
    }
    return -1;
}
 
// Solve x to power k ≡ a (mod n), n prime Prints all solutions using primitive root + BSGS 
void printDiscreteRoot(int k,int a,int n){
    if(a==0){cout<<"1\n0\n";return;}
    int g=PrimitiveRoot(n),phi=n-1;
    int sq=(int)sqrt(n)+1;
    vector<pair<int,int>>dec(sq);
    for(int i=1;i<=sq;i++)
        dec[i-1]={BigMod(g,1LL*i*sq%phi*k%phi,n),i};
    sort(dec.begin(),dec.end());
    int any=-1;
    for(int i=0;i<sq;i++){
        int val=1LL*BigMod(g,1LL*i*k%phi,n)*a%n;
        auto it=lower_bound(dec.begin(),dec.end(),make_pair(val,0));
        if(it!=dec.end()&&it->first==val){
            any=it->second*sq-i;
            break;
        }
    }
    if(any==-1){cout<<"0\n";return;}
    int delta=phi/__gcd(k,phi);
    vector<int>ans;
    for(int cur=(any%delta+delta)%delta;cur<phi;cur+=delta)
        ans.push_back(powmod(g,cur,n));
    sort(ans.begin(),ans.end());
    cout<<ans.size()<<"\n";
    for(int x:ans)cout<<x<<" ";
}
