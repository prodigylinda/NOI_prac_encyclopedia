#include<bits/stdc++.h>
using namespace std;
int n;
long long ans=0;
vector<int> all;
int find(vector<int>& all){
    int minnum=INT_MAX;
    for(int i=0;i<(int)all.size();i++){
        minnum=min(minnum,all[i]);
    }
    return minnum;
}
void chuli(vector<int>& all,long long& ans){
    if(all.empty()){
        return;
    }
    int tmp=find(all);
    int zhong;
    for(int i=0;i<all.size();i++){
        if(all[i]==tmp){
            zhong=i;
        }
        all[i]-=tmp;
    }
    ans+=tmp;
    vector<int> left(all.begin(),all.begin()+zhong);
    vector<int> right(all.begin()+zhong+1,all.end());
    chuli(left,ans);
    chuli(right,ans);
    return;
}
int main(){
    cin>>n;
    all.resize(n);
    for(int i=0;i<n;i++){
        cin>>all[i];
    }
    chuli(all,ans);
    cout<<ans<<endl;
    return 0;
}