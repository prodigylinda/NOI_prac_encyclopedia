#include<bits/stdc++.h>
#include<cmath>
#include<climits>
using namespace std;
int main(){
    freopen("detect.in","r",stdin);
    freopen("detect.out","w",stdout);
    int t;
    cin>>t;
    while(t--){
        long long n,m,l,v;
            long long  ans=0;
            cin>>n>>m>>l>>v;
            vector<vector<int>> all(n+1,vector<int>(3));
            long long ji=1;
            for(long long i=1;i<=n;i++){
                cin>>all[i][0]>>all[i][1]>>all[i][2];
            }
            int allc[m];
            for(int i=0;i<m;i++){
                cin>>allc[i];
            }
            vector<pair<int,int>> cnt(n+1,{-1,-1});
            vector<vector<int>> allfan(m);
            for(long long i=1;i<=n;i++){
                if(all[i][2]>0){
                    if(allc[m-1]>=all[i][0]&&(pow(all[i][1],2)+2*all[i][2]*(allc[m-1]-all[i][0]))>pow(v,2)){
                        ans++;
                        int le = 0;
                        int r=m-1;
                        while(le<r){
                            int mid = (le+r)/2;
                            if((pow(all[i][1],2)+2*all[i][2]*(allc[mid]-all[i][0]))>pow(v,2)){
                                cnt[i].first = allc[mid];
                                cnt[i].second= allc[m-1];
                                r=mid-1;
                            }else{
                                cnt[i].first = allc[mid];
                                cnt[i].second= allc[m-1];
                                le=mid+1;
                            }
                        }
                    }
                }else if(all[i][2]==0){
                    if(allc[m-1]>=all[i][0]&&all[i][1]>v){
                        ans+=1;
                        int le = 0;
                        int r=m-1;
                        while(le<r){
                            int mid = (le+r)/2;
                            if(allc[mid]>=all[i][0]){
                                cnt[i].first = allc[mid];
                                cnt[i].second= allc[m-1];
                                r=mid-1;
                            }else{
                                le=mid+1;
                            }
                        }
                    }
                }else{
                    int a;
                    for(int j=0;j<m;j++){
                        if(all[i][0]<=allc[j]){
                            a=allc[j]-all[i][0];
                            break;
                        }
                    }
                    if(allc[m-1]>=all[i][0]&&(pow(all[i][1],2)+2*all[i][2]*a)>pow(v,2)){
                        ans+=1;
                    }
                    int le = 0;
                    int r=m-1;
                    while(le<r){
                            int mid = (le+r)/2;
                            if((pow(all[i][1],2)+2*all[i][2]*(allc[mid]-all[i][0]))>pow(v,2)){
                                cnt[i].first = allc[mid];
                                cnt[i].second= allc[m-1];
                                le=mid+1;
                            }else{
                                cnt[i].first = allc[mid];
                                cnt[i].second= allc[m-1];
                                r=mid-1;
                            }
                        }
                } 
            }
            vector<int> xu;
            vector<pair<int,int>> youxiao;
            for(int i=0;i<cnt.size();i++){
                if(cnt[i].first==-1){
                    continue;
                }else{
                    youxiao.push_back(cnt[i]);
                }
            }
            for(int i =0;i<youxiao.size();i++){
                swap(youxiao[i].first,youxiao[i].second);
            }
            sort(youxiao.begin(),youxiao.end());
            for(int i =0;i<youxiao.size();i++){
                swap(youxiao[i].first,youxiao[i].second);
            }
            for(int i=0;i<youxiao.size();i++){
                if(!xu.empty()){
                    if(xu[xu.size()-1]<youxiao[i].first){
                        xu.push_back(youxiao[i].second);
                    }
                }else{
                    xu.push_back(youxiao[i].second);
                }
            }
            cout<<ans<<" "<<m-xu.size()<<endl;
    }
    return 0;
}