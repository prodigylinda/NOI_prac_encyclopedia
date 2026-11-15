#include<bits/stdc++.h>
using namespace std;
int main(){
    freopen("lock.in","r",stdin);
    freopen("lock.out","w",stdout);
    int n;
    cin>>n;
    int ans;
    vector<vector<int>> all(n+1,vector<int>(6));
    vector<vector<int>> po;
    vector<vector<int>> last;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=5;j++){
            cin>>all[i][j];
        }
        for(int k=1;k<=5;k++){
            for(int s=0;s<=9;s++){
                vector<int> newone;
                newone=all[i];
                if(newone[k]==s){
                    continue;
                }
                newone[k]=s;
                po.push_back(newone);
            }
        }
        for(int m=1;m<=4;m++){
            for(int f=1;f<=9;f++){
                vector<int> newone;
                newone = all[i];
                newone[m]=(newone[m]+f)%10;
                newone[m+1]=(newone[m+1]+f)%10;
                po.push_back(newone);
            }
        }
    }   
    for(int i=0;i<po.size();i++){
        if(count(po.begin(),po.end(),po[i])==n){
            last.push_back(po[i]);
        }else{
            continue;
        }
    }
    for(int i=0;i<last.size();i++){
        if(count(last.begin(),last.end(),last[i])!=1){
            last.erase(last.begin()+i);
            i-=1;
        }
    }
    ans = last.size();
    cout<<ans<<endl;
    return 0;
}