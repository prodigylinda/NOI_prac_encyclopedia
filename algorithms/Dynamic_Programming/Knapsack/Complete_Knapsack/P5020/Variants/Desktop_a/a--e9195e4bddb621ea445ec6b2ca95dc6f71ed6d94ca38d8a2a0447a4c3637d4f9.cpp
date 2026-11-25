#include<bits/stdc++.h>
using namespace std;
int t,n,ans;
vector<int> a;
vector<bool> all(25005);
int main(){
    all[0]=true;
    cin>>t;
    while(t--){
        ans=0;
        cin>>n;
        a.resize(n,0);
        fill(all.begin(),all.end(),false);
        for(int i=0;i<n;i++){
            cin>>a[i];
        }
        sort(a.begin(),a.end());
        for(int i=0;i<n;i++){
            int g=a[i];
            if(!all[g]){
                all[g]=true;
                ans++;
                for(int j=1;j<25005;j++){
                    if(all[j]&&j+g<=25005){
                        all[j+g]=true;
                    }
                }
            }else{
                continue;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}