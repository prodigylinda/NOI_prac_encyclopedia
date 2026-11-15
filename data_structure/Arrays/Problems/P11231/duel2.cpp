#include<bits/stdc++.h>
using namespace std;
int main(){
    freopen("duel.in","r",stdin);
    freopen("duel.out","w",stdout);
    int n;
    cin>>n;
    vector<int> all(n);
    for(int i=0;i<n;i++){
        cin>>all[i];
    }
    sort(all.begin(),all.end(),less<int>());
    int ans=1;
    int cnt=1;
    for(int i=1;i<n;i++){
        if(all[i-1]==all[i]){
            cnt+=1;
        }else{
            cnt=1;
        }


        ans=max(ans,cnt);
        //all.erase(all.begin()+i);
        //i--;
    }
    cout<<ans<<endl;
    return 0;
}