#include <bits/stdc++.h>
using namespace std;

struct Car {
    int d, v, a;
};

struct Interval {
    int l, r;
};

int main() {
    // 正式比赛使用文件输入输出时，取消下面两行的注释。
    // freopen("detect.in", "r", stdin);
    // freopen("detect.out", "w", stdout);

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n, m, L, V;
        cin >> n >> m >> L >> V;

        vector<Car> cars(n);

        for (int i = 0; i < n; i++) {
            cin >> cars[i].d >> cars[i].v >> cars[i].a;
        }

        // 测速仪编号使用 1 到 m。
        vector<int> p(m + 1);

        for (int i = 1; i <= m; i++) {
            cin >> p[i];
        }

        vector<Interval> intervals;

        for (int i = 0; i < n; i++) {
            int d = cars[i].d;
            int v = cars[i].v;
            int a = cars[i].a;

            // 找到第一个位置 >= d 的测速仪。
            int start = lower_bound(
                p.begin() + 1, p.end(), d
            ) - p.begin();

            // 所有测速仪都在车辆出发位置的南边。
            if (start == m + 1) {
                continue;
            }
            // 匀速：只需判断初速度。
            if (a == 0) {

                if (v > V) {
                    intervals.push_back({start, m});
                }
            } 
            // 加速：二分第一个查到超速的测速仪。
            if (a > 0) {
                int left = start;
                int right = m;
                int first = m + 1;

                while (left <= right) {
                    int mid = left + (right - left) / 2;

                    long long speed2 =
                        1LL * v * v
                        + 2LL * a * (p[mid] - d);

                    if (speed2 > 1LL * V * V) {
                        first = mid;
                        right = mid - 1;
                    } else {
                        left = mid + 1;
                    }
                }

                if (first <= m) {
                    intervals.push_back({first, m});
                }
            } 
            // 减速：如果第一个测速仪查不到， 后面的测速仪也查不到。
            if (a < 0){
                
                long long speed2 =
                    1LL * v * v
                    + 2LL * a * (p[start] - d);

                if (speed2 <= 1LL * V * V) {
                    continue;
                }

                // 二分最后一个查到超速的测速仪。
                int left = start;
                int right = m;
                int last = start;

                while (left <= right) {
                    int mid = left + (right - left) / 2;

                    long long currentSpeed2 =
                        1LL * v * v
                        + 2LL * a * (p[mid] - d);

                    if (currentSpeed2 > 1LL * V * V) {
                        last = mid;
                        left = mid + 1;
                    } else {
                        right = mid - 1;
                    }
                }

                intervals.push_back({start, last});
            }
        }

        // 第一问：存在非空检测区间的车辆数量。
        int caught = static_cast<int>(intervals.size());

        // 按右端点从小到大排序。
        sort(intervals.begin(), intervals.end(),
             [](const Interval& x, const Interval& y) {
                 return x.r < y.r;
             });

        int keep = 0;

        // 最近一次选择保留的测速仪编号。
        int selected = 0;

        for (const Interval& seg : intervals) {
            if (selected < seg.l) {
                // 当前区间没有被覆盖，选择其右端点。
                selected = seg.r;
                keep++;
            }
        }

        cout << caught << ' ' << m - keep << '\n';
    }

    return 0;
}