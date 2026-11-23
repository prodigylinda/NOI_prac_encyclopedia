#include<bits/stdc++.h>
using namespace std;
int n,m,u,v;
vector<vector<int>> g;
vector<int> ans;
vector<int> an;
vector<pair<int,int>> edges;
int dang1=-1,dang2=-1;
bool book[5005];
void dfs(int s){
    book[s]=true;
    an.push_back(s);
    for(auto a:g[s]){
        if((a==dang2&&s==dang1)||(a==dang1&&s==dang2)){
            continue;
        }
        if(!book[a]){
            book[a]=true;
            dfs(a);
        }
    }  
}
void solve(){
    memset(book,0,sizeof(book));
    dfs(1);
    if((int)an.size()!=n){
        return ;
    }
    if(ans.empty()||an<ans){
        ans=an;
    }
    return ;
}
int main(){
    cin>>n>>m;
    g.resize(n+1);
    for(int i=0;i<m;i++){
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
        edges.push_back({u,v});
    }
    for(int i=1;i<=n;i++){
        sort(g[i].begin(),g[i].end());
    }
    if(m==n-1){
        dfs(1);
    }else{
        for(auto a:edges){
            dang1=a.first;
            dang2=a.second;
            solve();
        }
    }
    for(int i=0;i<(int)ans.size();i++){
        cout<<ans[i]<<" ";
    }
    return 0;
}