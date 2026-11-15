#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,ans=LONG_LONG_MAX,all[55],cha[55],b[55],book[55];
void dfs(int x){
    if(x==n){
        int cnt =all[1],sum1=cnt*cnt,sum2=cnt;
        for(int i=1;i<n;i++){
            cnt+=b[i];
            sum1+=cnt*cnt;
            sum2+=cnt;  
        }
        ans=min(ans,n*sum1-sum2*sum2);
        return;
    }
    for(int i=1;i<n;i++){
        if(book[i]){
            continue;
        }
        book[i]=1;
        b[x]=cha[i];
        dfs(x+1);
        book[i]=0;
    }
    return;
}
signed main(){
    freopen("variance.in","r",stdin);
    freopen("variance.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>all[i];
    }
    for(int i=1;i<n;i++){
        cha[i]=all[i+1]-all[i];
    }
    dfs(1);
    cout<<ans<<endl;
    return 0;
}