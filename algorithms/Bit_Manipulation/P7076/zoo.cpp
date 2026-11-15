#include<bits/stdc++.h>
using namespace std;
int main(){
    freopen("zoo.in","r",stdin);
    freopen("zoo.out","w",stdout);
    int n,m,c,k;
    cin>>n>>m>>c>>k;
    unsigned long long all = 0;
    vector<unsigned long long> t(n+1);
    for(int i=1;i<=n;i++){
        cin>>t[i];
        all |= t[i];
    }
    vector<pair<int,int>> yao(m+1);
    for(int i=1;i<=m;i++){
        cin>>yao[i].first>>yao[i].second;
    }
    vector<bool> coun(k,true);
    for(int i=1;i<=m;i++){
        if(((all>>yao[i].first)&1)==0){
            coun[yao[i].first]=false;
        }else{
            coun[yao[i].first]=true;
        }
    }
    unsigned __int128 ans=1;
    for(int i=0;i<k;i++){
        if(coun[i]){
            ans*=2;
        }
    }
    int yuanans= ans-n;
    ans=ans-n;
    vector<int> lans;
    int i=0;
    while(ans>0){
        lans.push_back(ans%10);
        i++;
        ans/=10;
    }
    if(lans.size()==0){
        cout<<yuanans;
    }else{
        for(int i=lans.size()-1;i>=0;i--){
        cout<<lans[i];
        }
        cout<<""<<endl;
    }
}