#include<bits/stdc++.h>
using namespace std;
struct Node{
    int v;
    Node* next[3] = {nullptr, nullptr, nullptr}; // 三层指针
};
Node* head = nullptr; // 跳表头节点

bool find(int x){
    Node* p = head;
    if(p == nullptr) return false;
    // 从最高层向最低层搜索
    for(int i = 2; i >= 0; i--){
        // 当前层不断向右移动
        while(p->next[i] != nullptr &&
              p->next[i]->v < x){
            p = p->next[i]; // 移动到下一节点
        }
    }
    // 最后检查第0层的下一个节点
    p = p->next[0];
    return p != nullptr && p->v == x;
}

int main(){
    // 输入并构建跳表
    // 初始化 head，连接各层节点
    return 0;
}