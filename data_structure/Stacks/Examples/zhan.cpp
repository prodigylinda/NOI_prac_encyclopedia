#include<bits/stdc++.h>
using namespace std;
int main(){
    const int a=10;
    int st[a]={};
    int x=7;
    int y=9;
    st[++*st]=x;
    st[++*st]=y;
    int n = st[*st];
    cout<<n<<endl;
    if(*st){
        --*st;
    }
    int nn=st[*st];
    cout<<st[*st];
    return 0;
}