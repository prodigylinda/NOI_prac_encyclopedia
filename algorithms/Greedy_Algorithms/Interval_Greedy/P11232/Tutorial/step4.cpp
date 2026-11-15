// ============================================================================
// step4.cpp  ——  对应 step.md 的 Step 5（归约到模型）+ Step 6（正确性论证）
// ----------------------------------------------------------------------------
// 【相比 step3 的进展】
//   ✅ 第二问从 2^m 枚举 → O(k log k) 的**区间最小点覆盖贪心**（k = 区间数）
//   ✅ 第二问对所有 m 都正确，不再受 m ≤ 20 限制
//   ⬜ 建模层仍是 O(nm)，n,m = 10^5 时必然 TLE
//
// 【本步预计得分】≈60 分（测试点 1、2、3、5、7、9，即所有 n,m ≤ 3000 的点）
//   n,m ≤ 3000 时建模层约 9×10^6 次运算，乘以 T ≤ 20 约 1.8×10^8，
//   在 1s 时限下属于"可能过也可能超"的灰色地带；10^5 的点（4、6、8、10）必超。
//
// 【本步的核心思想：归约】
//   第二问一旦翻译成"用最少的点命中所有区间"，它就不再是一道新题，
//   而是**区间最小点覆盖（interval stabbing）**这个经典模型 —— 直接套贪心。
//   step.md「Step 5 归约到模型」的意义正在于此：
//   把陌生题映射到已知模型，算法就变成查表。
//
// 【复杂度】O(nm + k log k)，k ≤ n
//
// 【本步遗留 TODO】
//   TODO: 把建模层从 O(nm) 降到 O(n log m)（定向二分）    → step5.cpp
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
        // 【建模层】与 step2 / step3 完全相同（已验证正确，原样复用）
        // TODO: step5.cpp 将把这一段 O(nm) 的扫描替换为 O(n log m) 的定向二分
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
        // 【第二问 · 正解】区间最小点覆盖贪心
        // -------------------------------------------------------------------------
        //  算法：
        //    ① 把所有区间按**右端点 r 升序**排序；
        //    ② 维护 selected = 上一次选中的点（初值 0，因为下标从 1 开始，
        //       0 天然表示"还没选过任何点"，这就是哨兵的用处）；
        //    ③ 依次处理每个区间：若 selected < l（说明当前区间还没被命中），
        //       就选中它的**右端点** r，keep++。
        //
        //  为什么排序关键字必须是"右端点"？——【交换论证】(step.md Step 6)
        //    设最优解为 O，贪心解为 G。考察排序后的第一个区间 I₁ = [l₁, r₁]。
        //    G 选了 r₁；O 必须在 I₁ 中选某点 x，故 x ≤ r₁。
        //    把 O 中的 x 替换成 r₁：任何原本被 x 命中的区间 [l, r]，
        //    满足 l ≤ x ≤ r₁，且因排序有 r ≥ r₁，于是 l ≤ r₁ ≤ r，
        //    即 r₁ 也在该区间内 ⟹ 替换后仍是合法解，且 |O| 不变。
        //    对剩余区间归纳，得 |G| ≤ |O|，贪心最优。∎
        //
        //  反例攻击（自检：换成别的关键字会错）：
        //    · 按左端点排序 + 选左端点：区间 [1,10] 与 [2,3]，
        //      会选 1 和 2 共 2 个点，而最优是只选 3（或 2）一个点。✗
        //    · 按区间长度排序：同样可构造反例。✗
        //    ⟹ 右端点排序是必要的，不是随便挑的。
        //
        //  注意：比较器必须用严格的 `<`。写成 `<=` 会破坏严格弱序，
        //        std::sort 可能越界访问 ⟹ RE。
        // =====================================================================
        sort(intervals.begin(), intervals.end(),
             [](const Interval& x, const Interval& y) {
                 return x.r < y.r;
             });

        int keep = 0;
        int selected = 0;  // 哨兵：0 表示尚未选点（测速仪下标从 1 开始）

        for (const Interval& seg : intervals) {
            if (selected < seg.l) {
                // 当前区间未被命中 → 选它的右端点（能覆盖尽量多的后续区间）
                selected = seg.r;
                keep++;
            }
            // 否则 selected ∈ [seg.l, seg.r]？
            //   由排序知 seg.r ≥ selected，由判断知 selected ≥ seg.l，
            //   故 selected 确实落在本区间内，已被命中，无需再选点。
        }

        if (DEBUG_IR) {
            cerr << "caught=" << caught << " keep=" << keep << " closed=" << m - keep << '\n';
        }

        // ★ 输出的是"最多可以**关闭**的数量" = m - 最少保留数，别写反。
        cout << caught << ' ' << m - keep << '\n';
    }

    return 0;
}
