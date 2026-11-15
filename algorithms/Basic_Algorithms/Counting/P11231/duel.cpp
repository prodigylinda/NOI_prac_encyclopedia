#include<bits/stdc++.h>
#include<vector>
using namespace std;
int main(){
    freopen("duel.in","r",stdin);
    freopen("duel.ans","w",stdout);
    int n;
    cin>>n;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    vector<int> cnt(100000,0);
    for(int i=1;i<=n;i++){
        cnt[a[i]]+=1;
    }
    int ans = 0;
    for(int i=1;i<=n;i++){
        ans=max(ans,cnt[a[i]]);
    }
    cout<<ans<<endl;
    return 0;
}