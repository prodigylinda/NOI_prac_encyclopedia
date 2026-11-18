#include<bits/stdc++.h>
#include<cmath>
using namespace std;
int t,a,b,ans;
int main(){
    freopen("a.in","r",stdin);
    freopen("a.out","w",stdout);
    cin>>t;
    while(t--){
        cin>>a>>b;
        ans=a+b+a*b/__gcd(a,b);
        cout<<ans<<endl;
    }
    return 0;
}