#include<bits/stdc++.h>
using namespace std;
int main(){
    freopen("a.in","r",stdin);
    freopen("a.out","w",stdout);
    int n,m;
    cin>>n>>m;
    vector<pair<int,int>> all(m);
    long long ans=0;
    for(int i=0;i<m;i++){
        cin>>all[i].first>>all[i].second;
    }
    sort(all.begin(),all.end(),[](const pair<int,int>& a,const pair<int,int>& b){return a.first<b.first;});
    int i=0;
    while(n>0){
        if(n-all[i].second>=0){
            n-=all[i].second;
            ans+=all[i].second*all[i].first;
        }else{
            ans+=all[i].first*n;
            n=0;
        }
        i++;
    }
    cout<<ans<<endl;
    return 0;
}