#include<bits/stdc++.h>
using namespace std;
int a,b;
int main(){
    cin>>a>>b;
    int ans=((a*b)/__gcd(a,b))-a-b;
    cout<<ans<<endl;
    return 0;

}