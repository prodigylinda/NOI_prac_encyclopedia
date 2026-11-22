#include<bits/stdc++.h>
using namespace std;
int n,m;
vector<string> all;
vector<string> all1;
vector<string> all2;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    if(n==1){
        cout<<1<<endl;
        return 0;
    }
    all.resize(n);
    all1.resize(n);
    all2.resize(n);
    for(int i=0;i<n;i++){
        cin>>all[i];
        string tmp=all[i];
        sort(tmp.begin(),tmp.end(),[](const char& a,const char& b){return a<b;});
        all2[i]=tmp;
        sort(tmp.begin(),tmp.end(),[](const char& a,const char& b){return a>b;});
        all1[i]=tmp;
    }
    for(int i=0;i<n;i++){
        bool yes=true;
        for(int j=0;j<n;j++){
            if(i==j){
                continue;
            }
            if(all1[j]<=all2[i]){
                yes=false;
            }
        }
        if(yes){
            cout<<1;
        }else{
            cout<<0;
        }
    }
    return 0;
}