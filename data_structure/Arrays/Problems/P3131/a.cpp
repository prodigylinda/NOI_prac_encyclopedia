#include<bits/stdc++.h>
using namespace std;
int main(){
    freopen("a.in","r",stdin);
    freopen("a.out","w",stdout);
    int n;
    cin>>n;
    vector<long long> all(n+1,0);
    vector<long long> yu(n+1,0);
    vector<int> lei(7,-1);
    lei[0]=0;
    int ans = 0;
    for(int i=1;i<=n;i++){
        cin>>all[i];
        all[i]+=all[i-1];
        yu[i]=all[i]%7;
    }
    for(int i =1;i<=n;i++){
        if(lei[yu[i]]==-1){
            lei[yu[i]]=i;
        }
        ans = max(ans,i-lei[yu[i]]);
    }
    cout<<ans<<endl;
    return 0;
}