#include<bits/stdc++.h>
using namespace std;
int main(){
    freopen("lock.in","r",stdin);
    freopen("lock.out","w",stdout);
    int n;
    cin>>n;
    vector<vector<int>> all(n,vector<int>(5));
    vector<vector<int>> po;
    for(int i=0;i<n;i++){
        cin>>all[i][0]>>all[i][1]>>all[i][2]>>all[i][3]>>all[i][4];
        for(int j=0;j<5;j++){
            for(int k=1;k<=9;k++){
                vector<int> tmp=all[i];
                tmp[j]=(tmp[j]+k)%10;
                po.push_back(tmp);
            }
        }
        for(int m=0;m<4;m++){
            for(int l=1;l<=9;l++){
                vector<int> tmp2=all[i];
                tmp2[m]=(tmp2[m]+l)%10;
                tmp2[m+1]=(tmp2[m+1]+l)%10;
                po.push_back(tmp2);
            }
        }
    }
    vector<vector<int>> ans;
    for(int i=0;i<(int)po.size();i++){
        if(count(po.begin(),po.end(),po[i])>=n){
            ans.push_back(po[i]);
        }
    }
    for(int i=0;i<(int)ans.size();i++){
        if(count(ans.begin(),ans.end(),ans[i])!=1){
            ans.erase(ans.begin()+i);
        }
    }
    cout<<(int)po.size()<<endl;
    return 0;
}
