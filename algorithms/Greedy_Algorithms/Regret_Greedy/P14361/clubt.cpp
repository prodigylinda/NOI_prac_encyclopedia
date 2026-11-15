#include<bits/stdc++.h>
using namespace std;
void de(long long& ans,int d,vector<int> cnt){
    for(int i=0;i<d;i++){
        ans-=cnt[i];
    }
}
int main(){
    freopen("club.in","r",stdin);
    freopen("club.out","w",stdout);
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        long long ans=0;
        pair<int,int> all[n+1][4];
        for(int i=1;i<=n;i++){
            for(int j=1;j<=3;j++){
                cin>>all[i][j].first;
                all[i][j].second = j;
            }
        }
        for(int i=1;i<=n;i++){
            sort(all[i]+1,all[i]+4,greater<pair<int,int>>());
        }
        vector<int> cnt[4];
        for(int i=1;i<=n;i++){
            ans+=all[i][1].first;
            cnt[all[i][1].second].push_back(all[i][1].first-all[i][2].first);
        }
        for(int i=1;i<=3;i++){
            sort(cnt[i].begin(),cnt[i].end());
        }
        for(int i=1;i<=3;i++){
            if(cnt[i].size()>n/2){
                int d = cnt[i].size()-n/2;
                de(ans,d,cnt[i]);
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}