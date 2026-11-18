#include<bits/stdc++.h>
using namespace std;
long long qiuhe(const vector<long long>& all,long long h){
    long long ans=0;
    for(long long i=0;i<(long long)all.size();i++){
        if(all[i]>h){
            ans+=all[i]-h;
        }
    }
    return ans;
}
long long n,m,h;
int main(){
    cin>>n>>m;
    vector<long long> all(n);
    long long maxt=0;
    for(int i=0;i<n;i++){
        cin>>all[i];
        maxt=max(maxt,all[i]);
    }
    long long top=maxt,di=0;
    long long mid;
    while(di<=top){
        mid =(di+top)/2;
        long long tmp=qiuhe(all,mid);
        if(tmp>=m){
            h=mid;
            di=mid+1;
        }else{
            top=mid-1;
        }
    }
    cout<<h<<endl;
    return 0;

}