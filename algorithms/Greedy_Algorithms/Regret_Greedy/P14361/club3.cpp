#include<bits/stdc++.h>
using namespace std;
int main(){
    freopen("club.in","r",stdin);
    freopen("club.out","w",stdout);
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        vector<vector<pair<int,int>>> all(n,vector<pair<int,int>>(3));
        vector<vector<int>> s(4);
        int ans=0;
        for(int i=0;i<n;i++){
            cin>>all[i][0].first>>all[i][1].first>>all[i][2].first;
            all[i][0].second=1;
            all[i][1].second=2;
            all[i][2].second=3;
            sort(all[i].begin(),all[i].end(),greater<pair<int,int>>());
            s[all[i][0].second].push_back(all[i][0].first-all[i][1].first);
            ans+=all[i][0].first;
        }
        int cnt = max({(int)s[1].size(),(int)s[2].size(),(int)s[3].size()});
        if(cnt<=n/2){
            cout<<ans<<endl;
        }else{
            int da;
            for(int i=1;i<=3;i++){
                if(cnt==(int)s[i].size()){
                    da=i;
                }
            }
            sort(s[da].begin(),s[da].end(),less<int>());
            for(int i=0;i<cnt-n/2;i++){
                ans-=s[da][i];
            }
            cout<<ans<<endl;
        }
    }
    return 0;
}