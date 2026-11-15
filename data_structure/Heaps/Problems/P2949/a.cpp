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
    priority_queue<int,vector<int>,greater<int>> answer;
    sort(all.begin(),all.end(),[](const pair<int,int>&a,const pair<int,int>& b){return a.first<b.first;});
    for(int i=0;i<n;i++){
        if(answer.empty()||answer.size()<all[i].first){
            answer.push(all[i].second);
        }else if(answer.top()<all[i].second){
            answer.pop();
            answer.push(all[i].second);
        }
    }
    while(answer.size()>0){
        ans+=answer.top();
        answer.pop();
    }
    cout<<ans<<endl;
    return 0;
}