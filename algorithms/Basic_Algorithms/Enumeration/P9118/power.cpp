#include<bits/stdc++.h>
#include<cmath>
using namespace std;
#define int long long
int n,k,ans=0;
set<int> all;
void chuli(set<int>& all,int k,int n){
    for(int i=(k>2?k:3);i<=59;i++){
        for(int j=2;j<=n;j++){
            int tmp=1;
            for(int h=1;h<=i;h++){
                if(tmp>n/j){
                    tmp=n+1;
                    break;
                }
                tmp*=j;
            }
            if(tmp<=n){
                if(k==2){
                    int a =(int)sqrtl(tmp);
                    if(a*a!=tmp){
                        all.insert(tmp);
                    }
                }else{
                    all.insert(tmp);
                }
            }else{
                break;
            }
        }
    }
}
signed main(){
    cin>>n>>k;
    if(k==1){
        cout<<n<<endl;
        return 0;
    }
    if(k>=3){
        all.insert(1);
    }
    chuli(all,k,n);
    if(k==2){
        ans+=(int)sqrtl(n);
    }
    
    ans+=all.size();
    cout<<ans<<endl;
    return 0;
}