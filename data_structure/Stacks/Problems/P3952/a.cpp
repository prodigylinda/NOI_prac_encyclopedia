#include<bits/stdc++.h>
#include<string>
using namespace std;
int t,l;

int main(){
    cin>>t;
    while(t--){
        set<char> totaltmp;
        string o;
        string daan="";
        stack<char> st;
        int tmp1;
        bool yes=true;
        cin>>tmp1;
        cin>>o;
        if(tmp1%2==1){
            yes=false;
        }
        for(int i=0;i<tmp1;i++){
            char tmp2;
            cin>>tmp2;
            if(tmp2=='F'){
                char shu1;
                string shu2,shu3;
                cin>>shu1>>shu2>>shu3;
                if(totaltmp.count(shu1)){
                    yes=false;
                }
                totaltmp.insert(shu1);
                st.push(shu1);
                if(shu2!="n"&&shu3=="n"){
                    if(daan.size()!=0){
                        if(!st.empty()){
                            daan=daan+"^"+"n";
                        }
                    }else{
                        daan=daan+shu3;
                    }
                }
            }else{
                if(st.empty()){
                    yes=false;
                }else{
                    char x=st.top();
                    st.pop();
                    totaltmp.erase(x);
                }
            }
        }
        int tmpn=count(daan.begin(),daan.end(),'n');
        if(tmpn>=1){
            daan="n^"+to_string(tmpn);
        }
        if(daan!=""){
            daan="O("+daan+")";
        }else{
            daan="O(1)";
        }
        if(!st.empty()){
            yes=false;
        }
        
        if(!yes){
            cout<<"ERR"<<endl;
        }else if(o!=daan){
            cout<<"No"<<endl;
        }else{
            cout<<"Yes"<<endl;
        }
        
    }
    return 0;
}