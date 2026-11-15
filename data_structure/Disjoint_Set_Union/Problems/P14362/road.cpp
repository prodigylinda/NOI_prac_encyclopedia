#include<bits/stdc++.h>
#include<vector>
using namespace std;
struct Edge{
    int tou,wei,w;
};
struct DSU{
    vector<int> fa,sz;
    DSU(int n){
        fa.resize(n+1);
        sz.resize(n+1);
        for(int i=1;i<=n;i++){
            fa[i]=i;
            sz[i]=1;
        }
    }
    int find(int n){
        if(fa[n]==n){
            return n;
        }
        return find(fa[n]);
    }
    bool merge(int a,int b){
        int x=find(a);
        int y=find(b);
        if(x==y){
            return false;
        }
        if(sz[x]>sz[y]){
            fa[y]=x;
            sz[x]+=sz[y];
        }else{
            fa[x]=y;
            sz[y]+=sz[x];
        }
        return true;
    }
};
int main(){
    freopen("road.in","r",stdin);
    freopen("road.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m,k;
    cin>>n>>m>>k;
    vector<Edge> edges(m);
    for(int i=0;i<m;i++){
        cin>>edges[i].tou>>edges[i].wei>>edges[i].w;
    }
    sort(edges.begin(),edges.end(),[](const Edge& a,const Edge& b){return a.w<b.w;});
    DSU dsu(n);
    long long ans=0;
    long long cnt =0;
    for(const Edge& a:edges){
        if(dsu.merge(a.tou,a.wei)){
            ans+=a.w;
            cnt+=1;
        }
        if(cnt==n-1){
            break;
        }
    }
    if(k!=0){
        edges.resize(m+k*n);
        for(int i=0;i<k;i++){
            int fei;
            cin>>fei;
            for(int j=0;j<n;j++){
                cin>>edges[m+1+i*n+j].w;
                edges[m+1+i*n+j].tou=j+1;
                edges[m+1+i*n+j].wei=n+i+1;
            }
        }
        sort(edges.begin(),edges.end(),[](const Edge& a,const Edge& b){return a.w<b.w;});
        DSU dsu(n+k);
        long long ans=0;
        long long cnt =0;
        for(const Edge& a:edges){
            if(dsu.merge(a.tou,a.wei)){
                ans+=a.w;
                cnt+=1;
            }
            if(cnt==n+k-1){
                break;
            }
        }
        cout<<ans<<endl;
        return 0;
    }
    cout<<ans<<endl;
    return 0;
}