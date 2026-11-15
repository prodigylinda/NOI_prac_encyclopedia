#include <bits/stdc++.h>
using namespace std;

int main() {
    queue<int> q;  // 创建一个存整数的空队列

    q.push(7);     // 从队尾加入 7，队列：7
    q.push(9);     // 从队尾加入 9，队列：7、9
    q.push(5);     // 从队尾加入 5，队列：7、9、5
                   // 此时队头是 7，队尾是 5

    cout << q.front() << '\n';  // 查看队头，输出 7，不删除
    cout << q.back() << '\n';   // 查看队尾，输出 5，不删除
    cout << q.size() << '\n';   // 查看元素数量，输出 3
    cout << q.empty() << '\n';  // 判断是否为空，输出 0，表示不为空

    q.pop();                   // 删除队头的 7，队列变为：9、5
    cout << q.front() << '\n';  // 新队头是 9，输出 9

    q.emplace(6);  // 在队尾直接构造一个元素，这里效果与 push(6) 相同
                   // 队列变为：9、5、6

    queue<int> q2 = q;  // 创建 q2，并复制 q 的全部元素
    queue<int> q3;      // 创建一个空队列 q3
    q3 = q;            // 复制赋值，q3 变为：9、5、6

    q2.pop();  // 删除 q2 的队头，q2 变为：5、6；q 不受影响

    q.swap(q2);  // 交换两个队列的内容
                // q 变为：5、6；q2 变为：9、5、6

    while (!q.empty()) {          // 只要 q 不为空，就继续处理
        int x = q.front();       // 先取出队头的值
        q.pop();                 // 再删除队头
        cout << x << ' ';        // 依次输出：5 6
    }
    cout << '\n';                // 此时 q 已经为空

    queue<int> emptyQueue;       // 创建一个空队列
    q3.swap(emptyQueue);         // 将 q3 与空队列交换，清空 q3
                                // q3 原来的元素转移到了 emptyQueue

    return 0;  // 程序结束
}
