// ============================================================================
// step3.cpp  ——  对应 step.md 的 Step 3（子任务逆向工程：先把部分分锁死）
// ----------------------------------------------------------------------------
// 【相比 step2 的进展】
//   ✅ 第二问用 2^m 子集枚举求出**绝对正确**的最小保留数（m ≤ 20）
//   ✅ 至此样例输出 "3 3" 完全正确，测试点 1、2 拿满
//   ⬜ 建模层仍是 O(nm)
//   ⬜ 第二问在 m > 20 时爆炸
//
// 【本步预计得分】20 分（测试点 1：n,m≤10；测试点 2：n,m≤20）
//   ★ 为什么值得写这个"注定要被替换"的暴力？
//     (1) 立刻锁定 20 分，心态与排名都有底；
//     (2) 它是第二问的**判定标准**（oracle）：step4 的贪心是否正确，
//         不是靠"我觉得对"，而是靠与本步在小数据上逐组比对；
//     (3) 它逼你把第二问的**题意**理解到位 —— 尤其是
//         "不漏掉超速车" ⟺ "每个非空区间都被命中"这一步翻译。
//
// 【复杂度】O(nm + 2^m · m · 区间数)，m ≤ 20 时约 2×10^8 的最坏量级，
//           实际因为 break 提前退出会快很多；m > 20 直接放弃。
//
// 【本步遗留 TODO】
//   TODO: m > 20 时的第二问正解（区间最小点覆盖贪心）    → step4.cpp
//   TODO: 把建模层从 O(nm) 降到 O(n log m)               → step5.cpp
// ============================================================================

#include <bits/stdc++.h>
using namespace std;

struct Car {
    int d, v, a;
};

struct Interval {
    int l, r;
};

#define DEBUG_IR 0

int main() {
    // TODO: 最终交付版取消注释（见 step7.cpp）
    // freopen("detect.in", "r", stdin);
    // freopen("detect.out", "w", stdout);

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n, m, L, V;
        cin >> n >> m >> L >> V;
        (void)L;

        vector<Car> cars(n);
        for (int i = 0; i < n; i++) {
            cin >> cars[i].d >> cars[i].v >> cars[i].a;
        }

        vector<int> p(m + 1);
        for (int j = 1; j <= m; j++) {
            cin >> p[j];
        }

        const long long V2 = 1LL * V * V;

        // =====================================================================
        // 【建模层】与 step2 完全相同 —— 这一层已经验证正确，不再改动。
        //   step.md「Step 7 分层实现」的核心价值就体现在这里：
        //   本步只替换"算法层"，建模层原样复用，出 bug 时嫌疑范围极小。
        // =====================================================================
        vector<Interval> intervals;
        intervals.reserve(n);

        for (int i = 0; i < n; i++) {
            int d = cars[i].d, v = cars[i].v, a = cars[i].a;

            int start = lower_bound(p.begin() + 1, p.end(), d) - p.begin();
            if (start == m + 1) continue;

            int l = -1, r = -1;
            for (int j = start; j <= m; j++) {
                long long speed2 = 1LL * v * v + 2LL * a * (p[j] - d);
                if (speed2 > V2) {
                    if (l == -1) l = j;
                    r = j;
                }
            }
            if (l == -1) continue;

            intervals.push_back({l, r});
        }

        // =====================================================================
        // 【第一问】
        // =====================================================================
        int caught = static_cast<int>(intervals.size());

        // =====================================================================
        // 【第二问 · 暴力版】枚举"保留哪些测速仪"的所有子集
        // -------------------------------------------------------------------------
        //  题意翻译（这一步是本步的真正难点）：
        //    · 关闭测速仪只会让拍到的车变少，绝不会变多；
        //    · 要求"全开时超速的车，关闭后仍被判超速"
        //        ⟺ 每辆超速车至少还有一个开启的测速仪拍到它
        //        ⟺ 每个非空区间 [l_i, r_i] 中至少有一个下标属于保留集合 S；
        //    · 最多能关多少 ⟺ |S| 最小 ⟺ 答案 = m - min|S|。
        //
        //  用 bit j-1 表示下标为 j 的测速仪是否保留（下标从 1 开始）。
        //  "全保留"（mask = 全 1）一定合法，所以 keep 初值取 m 是安全的上界。
        // =====================================================================
        int keep = m;  // 最少需要保留的测速仪数量

        if (m <= 20) {
            for (int mask = 0; mask < (1 << m); mask++) {
                // 检查该保留方案是否命中所有区间
                bool ok = true;
                for (const Interval& seg : intervals) {
                    bool hit = false;
                    for (int j = seg.l; j <= seg.r; j++) {
                        if ((mask >> (j - 1)) & 1) {
                            hit = true;
                            break;
                        }
                    }
                    if (!hit) {
                        ok = false;
                        break;  // 一个区间没命中就够了，提前退出
                    }
                }
                if (ok) {
                    keep = min(keep, __builtin_popcount(static_cast<unsigned>(mask)));
                }
            }
        } else {
            // -----------------------------------------------------------------
            // TODO: m > 20 时 2^m 枚举爆炸，本步只能退化为"全保留"（keep = m，
            //       即 closed = 0）。这是合法解但绝非最优，测试点 3~10 会因此失分。
            //       → step4.cpp 用 O(n log n) 的区间最小点覆盖贪心解决。
            // -----------------------------------------------------------------
            keep = m;
        }

        if (DEBUG_IR) {
            cerr << "caught=" << caught << " keep=" << keep << " closed=" << m - keep << '\n';
        }

        cout << caught << ' ' << m - keep << '\n';
    }

    return 0;
}
