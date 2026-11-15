#include<bits/stdc++.h>
using namespace std;
int main(){
    freopen("replace.in","r",stdin);
    freopen("replace.out","w",stdout);
    int n,m;
    cin>>n>>m;
    vector<pair<string,string>> all;
    for(int i=0;i<n;i++){
        string x,y;
        cin>>all[i].first>>all[i].second;
    }
    int ans=0;
    for(int i=0;i<m;i++){
        pair<string,string> b;
        cin>>b.first>>b.second;
        for(int j=0;j<(int)all.size();j++){
            if(all[j]==b){
                cout<<1<<endl;
                break;
            }else{
                cout<<0<<endl;
                break;
                //if(all[i].first.find(b.first)!=string::npos){
                  //  int ans+=1;
                 //   cout<<ans<<endl;
                //}
            }
        }
    }
    return 0;
}