#include<bits/stdc++.h>
#include<cmath>
using namespace std;
int main(){
    freopen("a.in","r",stdin);
    freopen("a.out","w",stdout);
    int n;
    unsigned long long k,m;
    cin>>n>>k;
    bool reverse = false;
    m=(unsigned __int128)exp2(n)/2;
    for(int i =0;i<n;i++){
        if(k<m){
            m-=(unsigned __int128)exp2(n)/(unsigned __int128)exp2(i+2);
            cout<<(reverse?1:0);
            reverse = false;
        }else{
            m+=(unsigned __int128)exp2(n)/(unsigned __int128)exp2(i+2);
            cout<<(reverse?0:1);
            reverse = true;
            
        }
    }
    return 0;

}