#include<bits/stdc++.h>
using namespace std;
int n;
struct carpet{
    int qidianx,qidiany,chang,gao;
};
vector<carpet> carpets;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        carpet tmp;
        cin>>tmp.qidianx>>tmp.qidiany>>tmp.chang>>tmp.gao;
        carpets.push_back(tmp);
    }
    int c1,c2;
    cin>>c1>>c2;
    for(int i=(int)carpets.size()-1;i>=0;i--){
        if(c1>=carpets[i].qidianx&&c1<=carpets[i].qidianx+carpets[i].chang&&c2>=carpets[i].qidiany&&c2<=carpets[i].qidiany+carpets[i].gao){
            cout<<i+1<<endl;
            return 0;
        }
    }
    cout<<-1<<endl;
    return 0;
}