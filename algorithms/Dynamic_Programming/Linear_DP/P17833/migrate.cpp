#include<bits/stdc++.h>
using namespace std;
const int N =2e6+5;
#define int long long
int c,t,a[N],n,d,dp[5005][5005],pre[N],last[N],sum[N];
signed main(){
    freopen("migrate.in","r",stdin);
    freopen("mgrate.out","w",stdout);
    cin>>c>>t;
    while(t--){
        scanf("%lld%lld",&n,&d);
        for(int i=1;i<=n;i++){
            scanf("%lld",&a[i]);
        }
        int D = a[2]-a[1];
        int ans=0;
        if(c==11||c==12){
            int k=d/D;
            if(k<2){
                ans=0;
            }else{
                ans=max(ans,n-2*k+1);
            }
        }else{
            memset(pre,0,sizeof pre);
            memset(last,0,sizeof last);
            memset(dp,0,sizeof dp);
            for(int i=1;i<=n;i++){
                for(int j=i-1;j>=1;j--){
                    if(a[i]-a[j]<=d){
                        pre[i]=j;
                    }
                }
                for(int j=i+1;j<=n;j++){
                    if(a[j]-a[i]<=d){
                        last[i]=j;
                    }
                }
            }
            for(int i=1;i<=n;i++){
                dp[i][i]=1;
                int l=i,r=i;
                while(1){
                    int tr=last[r];
                    if(tr==r){
                        break;
                    }
                    sum[l-1]=0;
                    for(int j=l;j<=r;j++){
                        sum[j]=sum[j-1]+dp[i][j];
                    }
                    for(int j=r+1;j<=tr;j++){
                        int tl=max(pre[j],l);
                        dp[i][j]=sum[r]-sum[tl-1];
                    }
                    l=r+1;
                    r=tr;
                }            
            }
            for(int i=1;i<=n;i++){
                for(int j=1;j<=n;j++){
                    if(dp[i][j]==2){
                        ans+=1;
                    }
                }
            } 
        }
        cout<<ans<<endl;
    }
    return 0;
}