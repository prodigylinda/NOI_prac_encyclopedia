#include<bits/stdc++.h>
using namespace std;
bool zhao(const vector<int>& all,int l,int r){
    for(int i=l;i<=r;i++){
        if(all[i]==0){
            return false;
            break;
        }else{
            continue;
        }
    }
    return true;
}
long long so(const vector<int>& all,int l,int r,int m){
    if(r<l){
        return 0;
    }
    if(r==l){
        int ab=0;
        ab = all[l]-m;
        return ab;
    }
    int a=0;
    int minn=INT_MAX;
    int mid=0;
    for(int i=l;i<=r;i++){
        minn=min(minn,all[i]);
        if(minn==all[i]){
            mid = i;
        }
    }
    a=minn-m;
    a+=so(all,l,mid-1,minn);
    a+=so(all,mid+1,r,minn);
    return a;
}
int main(){
    freopen("road.in","r",stdin);
    freopen("road.out","w",stdout);
    int n;
    cin>>n;
    long long ans=0;
    vector<int> all;
    all.push_back(0);
    for(int i=1;i<=n;i++){
        int tmp;
        cin>>tmp;
        all.push_back(tmp);
    }
    ans=so(all,1,n,0);
    //for(int i=1;i<=n;i++){

        //for(int j=n;j>=i;j--){
            //if(zhao(all,i,j)){
                //for(int a=i;a<=j;a++){
                    //all[a]-=1;
               //}
                //ans+=1;
                //j++;
            //}else{
                //continue;
            //}
        //}
    //}
    cout<<ans<<endl;

}