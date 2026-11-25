#include<bits/stdc++.h>
using namespace std;
int n,k;
int a[5];
void dfs(int x){
    if(x==n){
        for(int i=0;i<n;i++){
            cout<<a[i]<<" ";
        }
        cout<<""<<endl;
        return;
    }
    for(int i=1;i<=k;i++){
        a[x]=i;
        dfs(x+1);
    }
}
int main(){
    cin>>n>>k;
    dfs(0);
    return 0;
}