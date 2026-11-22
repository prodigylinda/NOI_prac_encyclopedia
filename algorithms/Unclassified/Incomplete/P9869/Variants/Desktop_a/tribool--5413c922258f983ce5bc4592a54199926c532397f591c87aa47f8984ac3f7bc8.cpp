#include<bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int c, t;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> c >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        vector<pair<char, int>> shuzi(n + 1, make_pair('N', 0)); 
        for(int k = 0; k < m; k++){
            char y;
            cin >> y;
            if(y == 'T' || y == 'F' || y == 'U'){
                int a;
                cin >> a;
                shuzi[a].first = y;
            } else if (y == '+' || y == '-') {
                int a, b;
                cin >> a >> b;
            }
        }
        
        int ans = 0;
        for(int i = 1; i <= n; i++){
            if(shuzi[i].first == 'U'){
                ans++;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
