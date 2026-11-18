#include<bits/stdc++.h>
using namespace std;
int t,a,b,ans;
int main(){
    freopen("a.in","r",stdin);
    freopen("a.out","w",stdout);
    cin>>t;
    while(t--){
        cin>>a>>b;
        ans=a*b+a%b;
        int ab=a%b;
        int ba=b%a;
        while(1){
            if(ans!=a+b&&ans%a==ba&&ans%b==ab){
                break;
            }
            ans+=b;
        }
        cout<<ans<<endl;

    }
    return 0;
}