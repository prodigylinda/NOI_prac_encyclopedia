#include<bits/stdc++.h>
using namespace std;
//int ci(const vector<char>& all,char a,int m){
 //   int cnt =0;
  //  for(int i=0;i<m;i++){
//        if(all[i]==a){
  //          cnt+=1;
  //      }
  //  }
   // return cnt;
//}
int main(){
    freopen("game.in","r",stdin);
    freopen("game.out","w",stdout);
    int n;
    cin>>n;
    vector<char> all;
    for(int i=0;i<n;i++){
        char tmp;
        cin>>tmp;
        all.push_back(tmp);
    }
    long long ans=0;
    stack<int> qian;
    map<string,int> d;
    string s="";
    d[s]=1;
    vector<int> dp(n,0);
    for(int i=0;i<n;i++){
        if(qian.empty()||(!qian.empty()&&all[qian.top()]!=all[i])){
            qian.push(i);
            s.push_back(all[i]);
        }else{
            if(!qian.empty()){
                if(all[i]==all[qian.top()]){
                qian.pop();
                s.pop_back();
                }
            }
        }
        dp[i]=d[s];
        ans+=dp[i];
        d[s]++;
    }
    cout<<ans<<endl;
    return 0;
}