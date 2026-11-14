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
    long long ans=0;
    vector<bool> answer(n+1,true);
    answer[0]=false;
    sort(all.begin(),all.end(),[](const pair<int,int>&a,const pair<int,int>& b){return a.second>b.second;});
    for(int i=0;i<n;i++){
        for(int j=(all[i].first>n?n:all[i].first);j>0;j--){
            if(answer[j]==true){
                ans+=all[i].second;
                answer[j]=false;
                break;
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}