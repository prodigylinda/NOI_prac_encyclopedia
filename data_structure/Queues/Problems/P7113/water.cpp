#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
vector<vector<int>> all;
vector<__int128> anszi;
vector<__int128> ansmu;
vector<int> pai;
vector<int> in;
void print(__int128 x){
    if(x>=10){
        print(x/10);
    }
    cout<<(int)(x%10);
}
void bfs(){
    queue<int> q;
    for(int i=1;i<=n;i++){
        if(in[i]==0){
            q.push(i);
        }
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        if(all[u].empty()){
            continue;
        }
        ansmu[u]*=all[u].size();
        for(auto a:all[u]){
            __int128 gcdnum=ansmu[u]/__gcd(ansmu[a],ansmu[u])*ansmu[a];
            anszi[a]=anszi[a]*(gcdnum/ansmu[a])+anszi[u]*(gcdnum/ansmu[u]);
            ansmu[a]=gcdnum;
            __int128 gcdnum2=__gcd(anszi[a],ansmu[a]);
            anszi[a]/=gcdnum2;
            ansmu[a]/=gcdnum2;
            in[a]-=1;
            if(in[a]==0){
                q.push(a);
            }
        }
    }
}
signed main(){
    cin>>n>>m;
    in.resize(n+1);
    all.resize(n+1);
    anszi.resize(n+1);
    ansmu.resize(n+1,1);
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
            in[tmp2]+=1;
        }
    }
    for(int i=1;i<=m;i++){
        anszi[i]=1;
        ansmu[i]=1;
    }
    bfs();
    for(size_t i=0;i<pai.size();i++){
        print(anszi[pai[i]]);
        cout<<" ";
        print(ansmu[pai[i]]);
        cout<<" "<<endl;
    }
    return 0;
}