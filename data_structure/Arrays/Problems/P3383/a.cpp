#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,q;
vector<bool> all;
vector<int> po;
signed main(){
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>q;
    all.resize(n+1,false);
    for(int i=2;i<=n;i++){
        if(!all[i]){
            for(int j=i*i;j<=n;j+=i){
                all[j]=true;
            }
        }
    }
    for(int i=2;i<=n;i++){
        if(!all[i]){
            po.push_back(i);
        }
    }
    while(q--){
        int x;
        cin>>x;
        cout<<po[x-1]<<endl;
    }
    return 0;
}
    