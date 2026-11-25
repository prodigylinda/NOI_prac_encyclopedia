#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,answer=-1;
vector<pair<int,int>> all;
signed main(){
    cin>>n>>m;
    all.resize(n);
    int dui=LLONG_MAX;
    for(int i=0;i<n;i++){
        cin>>all[i].first>>all[i].second;
        dui=min(dui,all[i].first+all[i].second);
    }
    sort(all.begin(),all.end());
    int sum=0;
    for(int i=-1;i<n;i++){
        int ce=m;
        int ans=0;
        if(i>=0){
            sum+=all[i].first;
            ans+=i+1;
        }
        if(ce>=sum){
            ce-=sum;
        }else{
            break;
        }
        int tao=ce/dui;
        ans+=2*tao;
        answer=max(answer,ans);
    }
    cout<<answer<<endl;


    return 0;
}