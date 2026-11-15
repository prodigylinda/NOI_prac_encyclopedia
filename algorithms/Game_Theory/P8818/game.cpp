#include<bits/stdc++.h>
using namespace std;
int main(){
    freopen("game.in","r",stdin);
    freopen("game.out","w",stdout);
    int n,m,q;
    cin>>n>>m>>q;
    int a[n+1];
    int b[m+1];
    int c[n+1][m+1];
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=m;i++){
        cin>>b[i];
    }
    //for(int i=1;i<=n;i++){
        //for(int j=1;j<=m;j++){
            //c[i][j]=a[i]*b[j];
        //}
    //}
    int ans=0;
    while(q--){
        int l1,r1,l2,r2;
        cin>>l1>>r1>>l2>>r2;
        if(r1==l1){
            int mins=0;
            if(a[l1]<=0){
                for(int i=1;i<=m;i++){
                    mins = min(mins,b[i]);
                }
            }
            for(int i=1;i<=m;i++){
                mins = min(mins,b[i]);
            }
            ans= a[l1]*mins;
            cout<<ans;
            continue;
        }else if(r2==l2){
            int maxs=0;
            for(int i=1;i<=m;i++){
                maxs = max(maxs,a[i]);
            }
            ans= b[l2]*maxs;
            cout<<ans;
            continue;
        }else{
            sort(a+l1,a+r1+1,greater<int>());
            sort(b+l2,b+r2);
            if(b[l2]<=0){
                for(int i =l1;i<=r1;i++){
                    if(a[i]==0){
                        ans=0;
                    }else{
                        ans = max(ans,b[l2]*a[i]);
                    }
                }
                cout<<ans<<endl;
                continue;
            }else{
                ans = a[l1]*b[l2];
                cout<<ans<<endl;
                continue;
            }
        }
    }
    return 0;
}
