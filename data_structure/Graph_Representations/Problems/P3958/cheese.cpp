#include<bits/stdc++.h>
using namespace std;
bool pan(const vector<int>& a,const vector<int>& b,int r){
    unsigned long long tmp = (unsigned long long)(a[0]-b[0])*(a[0]-b[0]) + (unsigned long long)(a[1]-b[1])*(a[1]-b[1]) + (unsigned long long)(a[2]-b[2])*(a[2]-b[2]);
    if(tmp<=4ULL*r*r){
        return true;
    }else{
        return false;
    }
    return false;
}
bool dfs(vector<bool>& visited,const vector<vector<int>>& all,const vector<vector<int>>& lin,int i,int r,int h){
    if(all[i][2]+r>=h){
        return true;
    }
    visited[i]=true;
    for(int j=0;j<lin[i].size();j++){
        int a = lin[i][j];
        if(!visited[a]){
            if(dfs(visited,all,lin,a,r,h)){
                return true;
            }
        }
    }
    return false;
}
int main(){ 
    freopen("cheese.in","r",stdin);
    freopen("cheese.out","w",stdout);
    int t;
    cin>>t;
    while(t--){
        int n,h,r;
        cin>>n>>h>>r;
        vector<bool> visited(n,false);
        vector<vector<int>> all(n); 
        for(int i=0;i<n;i++){
            int x,y,z;
            cin>>x>>y>>z;
            all[i].push_back(x);
            all[i].push_back(y);
            all[i].push_back(z);
        }
        vector<vector<int>> lin(n);
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(i==j){
                    continue;
                }else{
                    if(pan(all[i],all[j],r)){
                        lin[i].push_back(j);
                    }
                }
            }
        }
        int s;
        bool shi = false;
        for(int i=0;i<n;i++){
            if(all[i][2]-r<=0){
                if(dfs(visited,all,lin,i,r,h)){
                    cout<<"Yes"<<endl;
                    shi=true;
                    break;
                }
            }else{
                continue;
            }
        }
        if(!shi){
            cout<<"No"<<endl;
        }
    }
    return 0;
}