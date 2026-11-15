#include<bits/stdc++.h>
#include<stack>
using namespace std;
vector<char> all;
vector<int> fa;
vector<int> top;
int main(){
    freopen("brackets.in","r",stdin);
    freopen("brackets.out","w",stdout);
    int n;
    cin>>n;
    fa.push_back(0);
    fa.push_back(1);
    all.push_back('1');
    for(int i=1;i<=n;i++){
        char tmp;
        cin>>tmp;
        all.push_back(tmp);
    }
    for(int i=2;i<=n;i++){
        int tmp;
        cin>>tmp;
        fa.push_back(tmp);
    }
    long long ans=0;
    for(int i=1;i<=n;i++){
        stack<int> zuo;//计数
        vector<int> dp(n+1,0);
        long long cnt=0;
        int j=i;
        vector<int> one;//括号组下标
        one.push_back('0');
        while(j>1){
            one.push_back(j);
            j=fa[j];
        }
        one.push_back(1);
        reverse(one.begin(),one.end());

        
        for(int k=0;k<one.size()-1;k++){
            if(all[one[k]]=='('){
                zuo.push(k);
            }else{
                if(!zuo.empty()){
                    int x=zuo.top();
                    zuo.pop();
                    dp[k]=1;
                    if(x>0){
                        dp[k]+=dp[x-1];
                    }
                    cnt+=dp[k];
                }
            }

        }
        ans^=(cnt*i);
    }
    //cout<<ans<<'\n';
    return 0;
}