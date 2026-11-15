#include<bits/stdc++.h>
using namespace std;
int main(){
    freopen("a.in","r",stdin);
    freopen("a.out","w",stdout);
    int n;
    cin>>n;
    vector<pair<int,int>> all(n);
    for(int i=0;i<n;i++){
        cin>>all[i].first>>all[i].second;
    }
    sort(all.begin(),all.end(),[](const pair<int,int>& a,const pair<int,int>& b){return a.second<b.second;});
    int tmp;
        int ans=0;
    for(int i=0;i<n;i++){
        if(i==0||all[i].first>=tmp){
            tmp=all[i].second;
            ans+=1;
        }
    }
    cout<<ans<<endl;
    return 0;
}