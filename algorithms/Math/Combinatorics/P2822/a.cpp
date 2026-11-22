#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,k,n,m;
int all[2005][2005];
int jiecheng(int a){
    int ans=1;
    for(int i=a;i>0;i--){
        ans*=(i%k);
        ans%=k;
    }
    return ans;
}
signed main(){
    cin>>t>>k;
    for(int i=0;i<=2000;i++){
        for(int j=0;j<=2000;j++){
            all[i][j]=jiecheng(i)/(jiecheng(j)*jiecheng(i-j));
        }
    }
    while(t--){
        int answer=0
        cin>>n>>m;
        for(int i=0;i<=n;i++){
            int minn=min(i,m);
            for(int j=0;j<=minn;j++){
                if(all[i][j]==0){ 
                    answer++;
                }
            }
        }
        cout<<answer<<endl;
    }
    return 0;
}