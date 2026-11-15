// ============================================================================
// step5.cpp  ——  对应 step.md 的 Step 2（复杂度预算）+ Step 4（结构六问之②③）
// ----------------------------------------------------------------------------
// 【相比 step4 的进展】★本步是整道题的"临门一脚"★
//   ✅ 建模层从 O(nm) 暴力扫描 → O(n log m) 的**定向二分**
//   ✅ 抽出 first_true / last_true 两个通用二分原语，消除 step4 之前的重复代码
//   ✅ 三个特殊性质分支（a=0 / a>0 / a<0）统一成"判方向 + 一次二分"
//   ✅ 至此算法层面完全正确且高效
//
// 【本步预计得分】100 分
//
// 【推导链条（step.md Step 2 的"数据范围反推"）】
//   n,m ≤ 10^5，T ≤ 20  ⟹ 预算 O(n log n)
//     ⟹ 每辆车最多只能花 O(log m)
//     ⟹ 必须二分
//     ⟹ 二分的前提是谓词单调
//     ⟹ 于是去证单调性（下面【引理】）
//     ⟹ 单调性成立 ⟹ 命中下标连续 ⟹ 只需二分出两个端点
//   ★ 数据范围不是装饰，它直接把算法逼出来了。
//
// 【引理（单调性）】
//   固定一辆车，令 f(j) = v² + 2a(p_j - d)。因为 p_j 严格递增，
//   f 是关于 j 的一次函数复合，斜率为 2a：
//     · a > 0：f 严格递增 ⟹ over(j) = [f(j) > V²] 形如 F…F T…T ⟹ 命中集是**后缀**
//     · a = 0：f 恒为 v² ⟹ over(j) 是常函数 ⟹ 全 T（v>V）或全 F（v≤V）
//     · a < 0：f 严格递减 ⟹ over(j) 形如 T…T F…F ⟹ 命中集是**前缀**
//   三种情况下命中集都是连续区间，故 IR = [l, r] 良定义。∎
//
// 【定向二分表（step.md Step 4 的可复用引理）】
//   ┌────────────┬──────────────────────┬────────────────────┐
//   │ 谓词形状   │ 左端点 l             │ 右端点 r           │
//   ├────────────┼──────────────────────┼────────────────────┤
//   │ F…F T…T    │ first_true(start, m) │ m（轴的右边界）    │
//   │ T…T F…F    │ start（轴的左边界）  │ last_true(start,m) │
//   │ 全 T       │ start                │ m                  │
//   │ 全 F       │ —（空 IR）           │ —                  │
//   └────────────┴──────────────────────┴────────────────────┘
//   a ≥ 0 走第一行（a=0 的全 T / 全 F 被 first_true 自动涵盖）；
//   a < 0 走第二行，且必须先验 over(start)：若第一个能拍到它的测速仪都没超速，
//   后面只会更慢 ⟹ 直接空 IR（这个剪枝同时保证 last_true 的初值安全）。
//
// 【复杂度】O(n log m + k log k)，k ≤ n。n=m=10^5 时约 1.7×10^6 + 排序，轻松通过。
//
// 【本步遗留 TODO】
//   TODO: 分层解耦，让暴力 IR 与二分 IR 可以编译期切换以便对拍   → step6.cpp
//   TODO: Step 8 审计加固 + 考场交付（freopen 等）               → step7.cpp
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

// -----------------------------------------------------------------------------
// 二分原语 ①：在 [lo, hi] 上找**第一个**使 pred 为真的下标。
//   前提：pred 形如 F…F T…T（单调不减）
//   返回：该下标；若全为假，返回 hi + 1（越界哨兵，天然表示"不存在"）
//   写法要点：
//     · lo <= hi + mid = lo + (hi-lo)/2：闭区间二分，不会死循环、不会溢出；
//     · 命中时先记录再向左收缩，保证拿到的是"第一个"。
// -----------------------------------------------------------------------------
template <class Pred>
int first_true(int lo, int hi, Pred pred) {
    int ans = hi + 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (pred(mid)) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return ans;
}

// -----------------------------------------------------------------------------
// 二分原语 ②：在 [lo, hi] 上找**最后一个**使 pred 为真的下标。
//   前提：pred 形如 T…T F…F（单调不增）
//   返回：该下标；若全为假，返回 lo - 1（越界哨兵）
// -----------------------------------------------------------------------------
template <class Pred>
int last_true(int lo, int hi, Pred pred) {
    int ans = lo - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (pred(mid)) {
            ans = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return ans;
}

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

        vector<int> p(m + 1);  // p[1..m] 严格递增 ⟹ 这是二分能用的前提
        for (int j = 1; j <= m; j++) {
            cin >> p[j];
        }

        const long long V2 = 1LL * V * V;

        vector<Interval> intervals;
        intervals.reserve(n);

        // =====================================================================
        // 【建模层 · 正解】每辆车 O(log m)
        // =====================================================================
        for (int i = 0; i < n; i++) {
            int d = cars[i].d, v = cars[i].v, a = cars[i].a;

            // ---- (1) 轴上的起点：第一个 p_j >= d ----
            // 用 >= 而非 > ，因为"驶入时若该位置有测速仪也要测速"（端点包含）。
            int start = lower_bound(p.begin() + 1, p.end(), d) - p.begin();
            if (start == m + 1) continue;  // 所有测速仪都在出发点南边 ⟹ 空 IR

            // ---- (2) 判定谓词 over(j)：全程整数，无开方无浮点 ----
            //   speed2 = v² + 2a(p_j - d)
            //   量级：|2a(p_j-d)| ≤ 2×10^3×10^6 = 2×10^9 ⟹ 必须 long long。
            //   注意 a<0 时 speed2 可能为负（车已停），负数 ≤ V² 自然判为不超速，
            //   这正是"L 用不到"的原因：中途驶离被公式自动处理了。
            auto over = [&](int j) -> bool {
                return 1LL * v * v + 2LL * a * (p[j] - d) > V2;  // ★ 严格大于
            };

            int l, r;
            if (a >= 0) {
                // ---- (3a) 谓词单调不减：命中集是后缀 [l, m] ----
                //   a = 0 且 v > V  ⟹ over 全真 ⟹ first_true 返回 start
                //   a = 0 且 v ≤ V  ⟹ over 全假 ⟹ first_true 返回 m+1 ⟹ 空 IR
                //   a > 0           ⟹ 标准的 F…F T…T
                //   三种情况被同一行代码涵盖，无需再对 a==0 单独分支。
                l = first_true(start, m, over);
                if (l > m) continue;  // 全程不超速 ⟹ 空 IR ⟹ 第一问不计数
                r = m;                // 递增 ⟹ 一旦超速就永远超速，直到北端
            } else {
                // ---- (3b) 谓词单调不增：命中集是前缀 [start, r] ----
                //   先验第一个能拍到它的测速仪：若它都没超速，后面只会更慢。
                //   这个剪枝既是正确性要求，也让 last_true 的结果必然 ≥ start。
                if (!over(start)) continue;
                l = start;
                r = last_true(start, m, over);
            }

            if (DEBUG_IR) {
                cerr << "car " << i << " (d=" << d << ",v=" << v << ",a=" << a
                     << ") -> [" << l << "," << r << "]\n";
            }

            intervals.push_back({l, r});
        }

        // =====================================================================
        // 【第一问】非空 IR 的个数
        // =====================================================================
        int caught = static_cast<int>(intervals.size());

        // =====================================================================
        // 【第二问】区间最小点覆盖贪心（与 step4 相同，含交换论证见 step4 注释）
        // =====================================================================
        sort(intervals.begin(), intervals.end(),
             [](const Interval& x, const Interval& y) {
                 return x.r < y.r;   // ★ 必须严格 <，否则破坏严格弱序 → RE
             });

        int keep = 0;
        int selected = 0;  // 哨兵 0 = 尚未选点

        for (const Interval& seg : intervals) {
            if (selected < seg.l) {
                selected = seg.r;
                keep++;
            }
        }

        cout << caught << ' ' << m - keep << '\n';
    }

    return 0;
}
