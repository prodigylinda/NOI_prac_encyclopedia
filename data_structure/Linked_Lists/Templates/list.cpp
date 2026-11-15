#include<bits/stdc++.h>
using namespace std;
struct Node{
    int v;
    Node* next;
};
int main(){
    int n;//总个数
    cin>>n;
    Node* head =nullptr;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        Node* p=new Node;
        p->v=x;
        p->next=head;
        head=p;
        while(p != nullptr){
            cout<<p->v<<endl;
            p=p->next;
        }
        //in
        while(p!=nullptr){
            Node* q=p->next;
            delete p;
            p=q;
        }
    }
    return 0;
    //delete
}