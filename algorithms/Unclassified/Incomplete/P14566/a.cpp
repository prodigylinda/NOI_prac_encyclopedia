#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,ans;
signed main(){
    cin>>t;
    while(t--){
        cin>>n;
        vector<int> all;
        all.resize(n);
        if(n==0||n==1){
            int tmp;
            cin>>tmp;
            ans=0;
            cout<<ans<<endl;
            continue;
        }
        for(int i=0;i<n;i++){
            cin>>all[i];
        }
        sort(all.begin(),all.end());
        int minnum=all[0];
        int second;
        int maxnum=all[n-1];
        for(int i=n-2;i>=0;i--){
            if(all[i]!=all[i+1]){
                second=all[i];
                break;
            }
        }
        
        ans=max(maxnum-minnum,second);
        cout<<ans<<endl;

    }
    return 0;
}