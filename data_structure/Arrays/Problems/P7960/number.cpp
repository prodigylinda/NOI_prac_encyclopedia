#include<bits/stdc++.h>
using namespace std;
#include<cmath>
bool has(int x){
    while(x){
        if(x%10==7){
            return true;
            
        }
        x/=10;
    }
    return false;
}
int main(){
    freopen("number.in","r",stdin);
    freopen("number.out","w",stdout);
    int t;
    cin>>t;
    const long long N =10000005;
    vector<bool> bad(N,true);
    vector<int> all;
    bad[0]=false;
    for(int i=1;i<N;i++){
        if(has(i)){
            for(long long j=i;j<N;j+=i){
                bad[j]=false;
            }
        }
    }
    for(int i=1;i<N;i++){
        if(bad[i]){
            all.push_back(i);
        }
    }
    while(t--){
        int n;
        cin>>n;
        if(bad[n]==false||n>N||n<0){
            cout<<-1<<endl;
            continue;
        }
        int po=0;
        int l=1,r=all.size()-1;
        while(l<=r){
            int mid = (l+r)/2;

            if(all[mid]==n){
                po=mid;
            }
            if(all[mid]>n){
                r=mid-1;
            }else{
                l=mid+1;
            }
            
        }
        cout<<all[po+1]<<endl;
       
    }
    return 0;
}