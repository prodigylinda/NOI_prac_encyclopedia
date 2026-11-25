#include<bits/stdc++.h>
using namespace std;
int n,m;
int dp[13005];
int main(){
    cin>>n>>m;
    for(int i=0;i<n;i++){
        int x,y;
        cin>>x>>y;
        for(int j=m;j>=x;j--){
            dp[j]=max(dp[j],dp[j-x]+y);
        }
    }
    cout<<dp[m]<<endl;
    return 0;
}