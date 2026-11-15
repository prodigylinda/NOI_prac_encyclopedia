#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k,v[105],ans;
const int MOD=998244353;
void dfs(int x,int cnt,int cf){
    if(x==n+1){
        int c=cnt,sum=0;
        while(c){
            c-=(-c&c);
            sum++;
        }
        if(sum<=k){
            ans=(ans+cf)%MOD;
        }
        return;
    }
    for(int i=0;i<=m;i++){
        dfs(x+1,cnt+(1<<i),cf*v[i]%MOD);
    }
}
signed main(){
    freopen("sequence.in","r",stdin);
    freopen("sequence.out","w",stdout);
    cin>>n>>m>>k;
    for(int i=0;i<=m;i++){
        cin>>v[i];
    }
    dfs(1,0,1);
    cout<<ans<<endl;
    return 0;
}