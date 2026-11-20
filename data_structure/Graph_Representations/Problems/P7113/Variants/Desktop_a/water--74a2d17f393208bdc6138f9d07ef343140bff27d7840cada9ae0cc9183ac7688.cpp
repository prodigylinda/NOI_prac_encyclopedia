#include<bits/stdc++.h>
using namespace std;
int n,m;
vector<vector<int>> all;
vector<double> ans;
vector<int> pai;
void bfs(int s){
    queue<int> q;
    q.push(s);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(auto a:all[u]){
            ans[a]+=ans[u]/all[u].size();
            q.push(a);
        }
        if(!all[u].empty()){
            ans[u]=0;
        }
    }
}
int main(){
    cin>>n>>m;
    all.resize(n+1);
    ans.resize(n+1);
    for(int i=1;i<=n;i++){
        int tmp;
        cin>>tmp;
        if(tmp==0){
            pai.push_back(i);
        }
        for(int j=1;j<=tmp;j++){
            int tmp2;
            cin>>tmp2;
            all[i].push_back(tmp2);
        }
    }
    for(int i=1;i<=m;i++){
        ans[i]=1;
    }
    for(int i=1;i<=m;i++){
        bfs(i);
    }
    for(int i=0;i<pai.size();i++){
        cout<<i+1<<" "<<(int)(10*ans[pai[i]])<<endl;
    }
    return 0;
}