#include<bits/stdc++.h>
using namespace std;
long long a,b,p,ans;
int main(){
    cin>>a>>b>>p;
    long long A=a,B=b;
    a%=p;
    ans=1;
    while(b>0){
        if(b%2==1){
            ans*=(a%p);
            ans%=p;
        }
        a*=(a%p);
        a%=p;
        b/=2;
    }
    ans%=p;
    cout<<A<<"^"<<B<<" "<<"mod"<<" "<<p<<"="<<ans;
    return 0;
}