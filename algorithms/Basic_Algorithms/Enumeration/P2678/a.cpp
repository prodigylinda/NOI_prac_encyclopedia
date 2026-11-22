#include<bits/stdc++.h>
using namespace std;
int l,n,m;
vector<int> all;
vector<int> presum;
int main(){
    cin>>l>>n>>m;
    all.resize(n);
    presum.resize(n);
    for(int i=0;i<n;i++){
        cin>>all[i];
    }
    for(int i=1;i<n;i++){
        presum[i]=all[i]-all[i-1];
    }
    int ans=INT_MAX;
    for(int i=0;i<n-m;i++){
        int j=i+m;
        ans=min(ans,all[j]-all[i]);
    }
    cout<<ans<<endl;
    return 0;

}