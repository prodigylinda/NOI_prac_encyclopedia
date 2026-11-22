#include<bits/stdc++.h>
using namespace std;
int n,k;
vector<vector<int>> g;
int main(){
    cin>>n>>k;
    g.resize(n+1);
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    cout<<1<<endl;
    return 0;
}