// ============================================================================
// step6.cpp  ——  对应 step.md 的 Step 7（分层实现）
// ----------------------------------------------------------------------------
// 【相比 step5 的进展】
//   算法与复杂度和 step5 完全一致（仍是 100 分的正解），本步做的是**工程重构**：
//   ✅ 拆成四层：I/O 层 → 建模层 → 算法层 → 输出层，层与层之间只通过数据结构通信
//   ✅ 建模层保留两个实现（暴力 / 二分），可用 -DUSE_BRUTE_IR 编译期切换
//   ✅ 因此"对拍"变成一条命令，而不是两份互相复制的代码
//
// 【为什么要多这一步？】—— step.md Step 7 的理由
//   1. **可替换**：部分分 → 正解只需换建模层，算法层一行不动（step3→step4 已验证）；
//   2. **可对拍**：暴力建模层是"绝对可信的慢实现"，二分建模层是"要验证的快实现"，
//      两者输出必须逐字节相同，否则说明单调性推理或二分边界有 bug；
//   3. **可定位**：WA 时先只测建模层（打印 IR），再只测算法层，嫌疑范围减半；
//   4. **可复用**：minStab() 是纯粹的"区间最小点覆盖"，与本题题意无关，
//      下一道区间打点题可以直接抄。
//
// 【四层架构图】
//      detect.in
//         │  ① I/O 层        readCase()      ── 只负责读，不含任何算法
//         ▼
//      TestCase{ n,m,L,V, cars[], p[] }
//         │  ② 建模层        buildIR()       ── 唯一含"题目语义"的一层
//         ▼                                     （谓词 over、起点 start、方向）
//      vector<Interval>  ← 这就是 IR
//         │  ③ 算法层        minStab()       ── 纯算法，不知道"测速仪"是什么
//         ▼
//      keep（最少保留数）
//         │  ④ 输出层        main            ── caught 与 m-keep 的格式化
//         ▼
//      detect.out
//
// 【对拍方法（step.md Step 8 的三件套）】
//   # 1) 编译两份可执行文件
//   g++ -std=c++14 -O2 -o fast  step6.cpp
//   g++ -std=c++14 -O2 -o brute step6.cpp -DUSE_BRUTE_IR
//   # 2) 随机生成小数据（务必刻意制造边界：v==V、p_j==d_i、空 IR、a<0 中途停车、n=1）
//   # 3) 逐组比对
//   ./fast  < rand.in   > a.out
//   ./brute < rand.in   > b.out
//   diff a.out b.out
//   # 也可以直接用 step3.cpp（2^m 枚举第二问）作为 brute，交叉验证贪心。
//
// 【复杂度】O(n log m + k log k)（默认）；-DUSE_BRUTE_IR 时 O(nm + k log k)
//
// 【本步遗留 TODO】
//   TODO: Step 8 的审计加固与考场交付细节（freopen、极限数据计时、清单核对）→ step7.cpp
// ============================================================================

#include <bits/stdc++.h>
using namespace std;

// =============================================================================
// 数据结构定义（层与层之间的"接口契约"）
// =============================================================================
struct Car {
    int d, v, a;
};

// IR：一辆车 ↔ 一段能拍到它超速的测速仪下标区间 [l, r]
struct Interval {
    int l, r;
};

// 一组测试数据的原始输入
struct TestCase {
    int n = 0, m = 0, L = 0, V = 0;
    vector<Car> cars;
    vector<int> p;  // 下标 1..m；p[0] 不使用
};

#define DEBUG_IR 0

// =============================================================================
// 二分原语（属于"算法层工具"，与题意无关）
// =============================================================================

// 在 [lo,hi] 上找第一个使 pred 为真的下标；前提 pred 形如 F…F T…T；全假返回 hi+1
template <class Pred>
int first_true(int lo, int hi, Pred pred) {
    int ans = hi + 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (pred(mid)) { ans = mid; hi = mid - 1; }
        else           { lo = mid + 1; }
    }
    return ans;
}

// 在 [lo,hi] 上找最后一个使 pred 为真的下标；前提 pred 形如 T…T F…F；全假返回 lo-1
template <class Pred>
int last_true(int lo, int hi, Pred pred) {
    int ans = lo - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (pred(mid)) { ans = mid; lo = mid + 1; }
        else           { hi = mid - 1; }
    }
    return ans;
}

// =============================================================================
// ① I/O 层：只管读，不含任何算法与判断
// =============================================================================
TestCase readCase() {
    TestCase tc;
    cin >> tc.n >> tc.m >> tc.L >> tc.V;   // tc.L 读入但不使用（见下方说明）

    tc.cars.resize(tc.n);
    for (int i = 0; i < tc.n; i++) {
        cin >> tc.cars[i].d >> tc.cars[i].v >> tc.cars[i].a;
    }

    tc.p.assign(tc.m + 1, 0);              // 下标 1..m，0 与 m+1 作为哨兵
    for (int j = 1; j <= tc.m; j++) {
        cin >> tc.p[j];
    }
    return tc;
}

// =============================================================================
// ② 建模层 · 实现 A（暴力，O(nm)）—— 慢但绝对可信，专用于对拍
//    顺便自检【引理】：命中的下标必须连续（cnt == r-l+1）
// =============================================================================
vector<Interval> buildIR_brute(const TestCase& tc) {
    const long long V2 = 1LL * tc.V * tc.V;
    vector<Interval> ir;
    ir.reserve(tc.n);

    for (int i = 0; i < tc.n; i++) {
        int d = tc.cars[i].d, v = tc.cars[i].v, a = tc.cars[i].a;

        int start = lower_bound(tc.p.begin() + 1, tc.p.end(), d) - tc.p.begin();
        if (start == tc.m + 1) continue;

        int l = -1, r = -1, cnt = 0;
        for (int j = start; j <= tc.m; j++) {
            long long speed2 = 1LL * v * v + 2LL * a * (tc.p[j] - d);
            if (speed2 > V2) {
                if (l == -1) l = j;
                r = j;
                cnt++;
            }
        }
        if (l == -1) continue;

        if (DEBUG_IR && cnt != r - l + 1) {
            cerr << "!!! 连续性被破坏，单调性推理有误 !!!\n";
        }
        ir.push_back({l, r});
    }
    return ir;
}

// =============================================================================
// ② 建模层 · 实现 B（定向二分，O(n log m)）—— 正解
//    依赖【引理】f(j) = v² + 2a(p_j - d) 关于 j 单调：
//      a ≥ 0 → 命中集是后缀 [first_true(start,m), m]
//      a < 0 → 命中集是前缀 [start, last_true(start,m)]（先验 over(start)）
// =============================================================================
vector<Interval> buildIR_fast(const TestCase& tc) {
    const long long V2 = 1LL * tc.V * tc.V;
    vector<Interval> ir;
    ir.reserve(tc.n);

    for (int i = 0; i < tc.n; i++) {
        int d = tc.cars[i].d, v = tc.cars[i].v, a = tc.cars[i].a;

        // 轴上的起点：第一个 p_j >= d（端点包含：驶入处有测速仪也要测）
        int start = lower_bound(tc.p.begin() + 1, tc.p.end(), d) - tc.p.begin();
        if (start == tc.m + 1) continue;   // 空 IR

        // 判定谓词：全程整数，无开方、无浮点（题面明确警告精度问题）
        auto over = [&](int j) -> bool {
            return 1LL * v * v + 2LL * a * (tc.p[j] - d) > V2;   // ★ 严格大于
        };

        int l, r;
        if (a >= 0) {
            l = first_true(start, tc.m, over);
            if (l > tc.m) continue;        // 全程不超速 ⟹ 空 IR
            r = tc.m;
        } else {
            if (!over(start)) continue;    // 第一个都拍不到，后面更慢 ⟹ 空 IR
            l = start;
            r = last_true(start, tc.m, over);
        }

        if (DEBUG_IR) {
            cerr << "car " << i << " -> [" << l << "," << r << "]\n";
        }
        ir.push_back({l, r});
    }
    return ir;
}

// 建模层统一入口：编译期切换，便于对拍
inline vector<Interval> buildIR(const TestCase& tc) {
#ifdef USE_BRUTE_IR
    return buildIR_brute(tc);
#else
    return buildIR_fast(tc);
#endif
}

// =============================================================================
// ③ 算法层：区间最小点覆盖（interval stabbing）
//    纯粹的算法，完全不知道"测速仪""超速"是什么 —— 可跨题复用。
//    返回：命中所有区间所需的最少点数。
//    正确性：交换论证（详见 step4.cpp 注释）。
//    注意：按值传参，因为内部要排序，不应污染调用方的 IR。
// =============================================================================
int minStab(vector<Interval> segs) {
    if (segs.empty()) return 0;

    sort(segs.begin(), segs.end(),
         [](const Interval& x, const Interval& y) { return x.r < y.r; });

    int keep = 0;
    int selected = 0;                      // 哨兵 0 = 尚未选点（下标从 1 开始）
    for (const Interval& s : segs) {
        if (selected < s.l) {              // 当前区间未被命中
            selected = s.r;                // 选右端点，覆盖尽量多的后续区间
            keep++;
        }
    }
    return keep;
}

// =============================================================================
// ④ 输出层 + 主流程：只做组装，不做计算
// =============================================================================
int main() {
    // TODO: 最终交付版取消注释（见 step7.cpp）
    // freopen("detect.in", "r", stdin);
    // freopen("detect.out", "w", stdout);

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        TestCase tc = readCase();                 // ① I/O 层

        vector<Interval> ir = buildIR(tc);        // ② 建模层 → IR

        int caught = static_cast<int>(ir.size()); // ③ 第一问 = IR 的聚合
        int keep   = minStab(ir);                 // ③ 第二问 = IR 上的最优化

        // ④ 输出层：第二个数是"最多可**关闭**的数量" = m - 最少保留数
        cout << caught << ' ' << tc.m - keep << '\n';
    }

    return 0;
}
