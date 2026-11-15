#include<bits/stdc++.h>
using namespace std;
int main(){
    freopen("candy.in","r",stdin);
    freopen("candy.out","w",stdout);
    int n;
    long long h;
    cin>>n>>h;
    long long answer=0;
    vector<pair<int,int>> all(n);
    for(int i=0;i<n;i++){
        cin>>all[i].first>>all[i].second;
    }
    sort(all.begin(),all.end(),[](const pair<int,int>& a,const pair<int,int>& b){return a.first+a.second<b.first+b.second;});
    int da1=all[0].first+all[0].second;
    sort(all.begin(),all.end(),[](const pair<int,int>& a,const pair<int,int>& b){return a.first<b.first;});
    vector<long long> qian(n+1,0);

    qian[1]=all[0].first;
    for(int i=2;i<=n;i++){
        qian[i]=qian[i-1]+all[i-1].first;
    }


    for(int i=0;i<=n;i++){
        long long m=h;
        long long ans=0;
        if(m>=qian[i]){
            m-=qian[i];
            ans+=i;
        }else{
            break;
        }
        long long a=m/da1;
        ans+=a*2;
        //if(i!=0){
       //     if(m>=dah){
      //          ans+=1;
      ///          m-=dah;
      //      }
     //   }else{
    //        if(m>=daq){
    //            ans+=1;
     //           m-=daq;
      //      }
      //  }
        answer=max(ans,answer);
    }
    cout<<answer<<endl;
    return 0;
}