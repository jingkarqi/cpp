#include <array>
#include <climits>
#include <iostream>
#include <vector>

constexpr int w = 6;                // 内存工作区容量
constexpr int INFINITY_KEY = INT_MAX;

using KeyType = int;

struct RcdNode {
    KeyType key = INFINITY_KEY;
    int rnum = 0;  // 归并段段号
};

using WorkArea = std::array<RcdNode, w>;
using LoserTree = std::array<int, w>;  // 仅保留根（最小者）索引用于演示

bool lessRec(const RcdNode& a, const RcdNode& b) {
    if (a.rnum != b.rnum) return a.rnum < b.rnum;
    if (a.key != b.key) return a.key < b.key;
    return false;
}

int minimaxIndex(const WorkArea& wa) {
    int best = 0;
    for (int i = 1; i < w; ++i) {
        if (lessRec(wa[i], wa[best])) best = i;
    }
    return best;
}

void Construct_LoserTree(LoserTree& ls, const WorkArea& wa) {
    ls.fill(0);
    ls[0] = minimaxIndex(wa);
}

void Adjust_LoserTree(LoserTree& ls, const WorkArea& wa, int /*q*/) { ls[0] = minimaxIndex(wa); }

void Replace_Selection(LoserTree& ls, WorkArea& wa, const std::vector<KeyType>& input, std::vector<RcdNode>& output,
                       int& maxRun) {
    int rc = 1, max = 1;
    int pos = 0;

    // 读入 w 个记录
    for (int i = 0; i < w; ++i) {
        wa[i].key = (pos < static_cast<int>(input.size())) ? input[pos++] : INFINITY_KEY;
        wa[i].rnum = rc;
    }
    Construct_LoserTree(ls, wa);

    while (rc <= max) {
        int q = ls[0];
        KeyType minimax = wa[q].key;
        output.push_back(wa[q]);  // 输出 MINIMAX

        // 补充新记录
        if (pos >= static_cast<int>(input.size())) {
            wa[q].key = INFINITY_KEY;
            wa[q].rnum = max + 1;  // 无新记录：标记为“虚段”，用于终止
        } else {
            wa[q].key = input[pos++];
            if (wa[q].key < minimax) {
                wa[q].rnum = ++max;  // 归为新段
            } else {
                wa[q].rnum = rc;  // 归为当前段
            }
        }

        Adjust_LoserTree(ls, wa, q);
        rc = wa[ls[0]].rnum;
    }

    maxRun = max;
    output.push_back({INFINITY_KEY, 0});  // 段结束标志（EOF）
}

int main() {
    std::vector<KeyType> input = {20, 10, 30, 25, 40, 15, 5, 35, 12, 28, 8, 45, 18, 2, 50, 6, 22};

    LoserTree ls{};
    WorkArea wa{};
    std::vector<RcdNode> output;
    int maxRun = 0;

    Replace_Selection(ls, wa, input, output, maxRun);

    std::cout << "Input:";
    for (auto k : input) std::cout << ' ' << k;
    std::cout << '\n';

    std::cout << "Runs(max=" << maxRun << "):\n";
    int current = -1;
    for (const auto& rec : output) {
        if (rec.key == INFINITY_KEY && rec.rnum == 0) break;
        if (rec.rnum != current) {
            if (current != -1) std::cout << '\n';
            current = rec.rnum;
            std::cout << "Run" << current << ":";
        }
        std::cout << ' ' << rec.key;
    }
    std::cout << '\n';
    std::cout << "EndFlag=INF\n";
    return 0;
}

