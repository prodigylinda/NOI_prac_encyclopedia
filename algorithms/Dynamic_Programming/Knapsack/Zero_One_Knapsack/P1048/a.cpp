#include<bits/stdc++.h>
using namespace std;
int t,m,ans=0;
int dp[1005];
int main(){
    cin>>t>>m;
    for(int i=0;i<m;i++){
        int x,y;
        cin>>x>>y;
        if(x>t){
            continue;
        }
        for(int j=t;j>=x;j--){
            dp[j]=max(dp[j],dp[j-x]+y);
        }
    }
    cout<<dp[t]<<endl;
    return 0;
}