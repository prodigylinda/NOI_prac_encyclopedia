#include<bits/stdc++.h>
#include<utility>
using namespace std;
int main(){
    freopen("a.in","r",stdin);
    freopen("a.out","w",stdout);
    int n;
    cin>>n;
    vector<string> all(n);
    for(int i=0;i<n;i++){
        cin>>all[i];
    }
    sort(all.begin(),all.end(),[](const string& a,const string& b){return a+b>b+a;});
    for(int i=0;i<n;i++){
        cout<<all[i];
    }
    cout<<" "<<endl;
    return 0;
}
