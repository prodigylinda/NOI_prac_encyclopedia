#include<bits/stdc++.h>
using namespace std;
int main(){
    freopen("r.in","r",stdin);
    freopen("r.out","w",stdout);
    int n,m;
    cin>>n>>m;
    vector<pair<int,string>> all(n);
    for(int i=0;i<n;i++){
        cin>>all[i].first>>all[i].second;
    }
    int ans=0;
    while(m--){
        int fang;
        cin>>fang;
        int tmp;
        cin>>tmp;
        if(fang==1){
            if(all[ans].first==0){
                ans=(ans+tmp)%n;
                //cout<<ans<<endl;
            }else{
                ans=(ans+n-tmp)%n;
                //cout<<ans<<endl;
            }
        }else{
            if(all[ans].first==0){
                ans=(ans+n-tmp)%n;
                //cout<<ans<<endl;
            }else{
                ans=(ans+tmp)%n;
                //cout<<ans<<endl;
            }
        }
    }
    string answer = all[ans].second;
    cout<<answer<<endl;
    return 0;
}
