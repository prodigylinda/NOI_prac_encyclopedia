#include<bits/stdc++.h>
using namespace std;
int main(){
    //freopen("a.in","r",stdin);
    //freopen("a.out","w",stdout);
    long long n;
    cin>>n;
    vector<pair<int,int>> all(n);
    for(int i=0;i<n;i++){
        cin>>all[i].first;
        all[i].second=i+1;
    }
    sort(all.begin(),all.end());
    for(int i=0;i<n;i++){
        cout<<all[i].second<<" ";
    }
    cout<<" "<<endl;
    long long to=0;
    for(int i=0;i<n;i++){
        to+=all[i].first*(n-i-1);
        
    }
    double ans=(double)to/n;
    cout<<fixed<<setprecision(2)<<ans<<endl;
    return 0;
}