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
    vector<int> answer;
    sort(all.begin(),all.end(),[](const pair<int,int>&a,const pair<int,int>& b){return a.second>b.second;});
    for(int i=0;i<n;i++){
        if(answer.empty()){
            answer.push_back(all[i].first);
            ans+=all[i].second;
        }else if(count(answer.begin(),answer.end(),all[i].first)!=0){
            continue;
        }else{
            answer.push_back(all[i].first);
            ans+=all[i].second;
        }
    }
    cout<<ans<<endl;
    return 0;
}