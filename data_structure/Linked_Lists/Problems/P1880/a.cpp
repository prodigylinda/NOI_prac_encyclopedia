#include<bits/stdc++.h>
using namespace std;
int n;
vector<dot> all;
struct dot{
    int v,next;
}
int main(){
    cin>>n;
    all.resize(n);
    for(int i=0;i<n;i++){
        cin>>all[i].v;
        if(i!=n-1){
            all[i].next=i+1;
        }else{
            all[i].next=0;
        }
        

    }

}