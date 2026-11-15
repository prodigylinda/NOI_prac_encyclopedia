#include<bits/stdc++.h>
#include<cmath>
using namespace std;
int main(){
    freopen("a.in","r",stdin);
    freopen("ma.out","w",stdout);
    unsigned long long n,k;
    cin>>n>>k;
    unsigned long long mid=exp2(n)/2;
    bool reverse = false;
    for(int i=1;i<=n;i++){
        if(k<mid){
            mid-=(__int128)exp2(n)/(__int128)exp2(i+1);
            cout<<(reverse?1:0);
            reverse = false;
        }else{
            cout<<(reverse?0:1);
            mid+=(__int128)exp2(n)/(__int128)exp2(i+1);
            reverse=true;
        }
    }
    return 0;
}