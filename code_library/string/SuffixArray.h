void suffix_array(string s){
   s+="$";
   int32_t n=s.size(),N=max(n,int32_t(260));
   vector<int32_t> sa(n),R(n);
   for(int32_t i=0;i<n;i++)  sa[i]=i,  R[i]=s[i];
   for(int32_t k=0;k<n;k?(k<<=1):k++){
      vector<int32_t> nR(n),cnt(N);
      auto nsa=sa;
      for(int32_t i=0;i<n;i++) nsa[i]=(nsa[i]-k+n)%n,  cnt[R[i]]++;
      for(int32_t i=1;i<N;i++) cnt[i]+=cnt[i-1];
      for(int32_t i=n-1;i>=0;i--) sa[--cnt[R[nsa[i]]]]=nsa[i];
      for(int32_t i=1,r=0;i<n;i++){
         r+=(R[sa[i]]!=R[sa[i-1]] || R[(sa[i]+k)%n]!=R[(sa[i-1]+k)%n]);
         nR[sa[i]]=r;
      }  
      swap(R,nR);
   }
   vector<int32_t> lcp(n-1);
   for(int32_t i=0,k=0;i<n-1;i++){
      int32_t pi=R[i];
      int32_t j=sa[pi-1];
      while(i+k<n && j+k<n && s[i+k]==s[j+k])   k++;
      lcp[pi-1]=k;
      if(k) k--;
   }
}