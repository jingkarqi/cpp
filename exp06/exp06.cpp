#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct HTNode {
    unsigned int weight = 0;
    int parent = 0;
    int lchild = 0;
    int rchild = 0;
};

using HuffmanTree = std::vector<HTNode>;        // 结点从 1 开始编号
using HuffmanCode = std::vector<std::string>;  // 编码从 1 开始编号

enum Status { OK = 1, ERROR = 0 };

bool lessNode(const HuffmanTree& ht, int a, int b) {
    if (ht[a].weight != ht[b].weight) return ht[a].weight < ht[b].weight;
    return a < b;
}

void Select(const HuffmanTree& ht, int end, int& s1, int& s2) {
    s1 = s2 = 0;
    for (int i = 1; i <= end; ++i) {
        if (ht[i].parent != 0) continue;
        if (s1 == 0 || lessNode(ht, i, s1)) {
            s2 = s1;
            s1 = i;
        } else if (s2 == 0 || lessNode(ht, i, s2)) {
            s2 = i;
        }
    }
    if (s1 != 0 && s2 != 0 && lessNode(ht, s2, s1)) std::swap(s1, s2);
}

Status HuffmanCoding(HuffmanTree& ht, HuffmanCode& hc, const std::vector<unsigned int>& w) {
    const int n = static_cast<int>(w.size());
    if (n <= 1) return ERROR;

    const int m = 2 * n - 1;
    ht.assign(m + 1, HTNode{});

    for (int i = 1; i <= n; ++i) {
        ht[i].weight = w[i - 1];
        ht[i].parent = ht[i].lchild = ht[i].rchild = 0;
    }

    for (int i = n + 1; i <= m; ++i) {
        ht[i].weight = 0;
        ht[i].parent = ht[i].lchild = ht[i].rchild = 0;
    }

    for (int i = n + 1; i <= m; ++i) {
        int s1 = 0, s2 = 0;
        Select(ht, i - 1, s1, s2);
        if (s1 == 0 || s2 == 0) return ERROR;
        ht[s1].parent = i;
        ht[s2].parent = i;
        ht[i].lchild = s1;
        ht[i].rchild = s2;
        ht[i].weight = ht[s1].weight + ht[s2].weight;
    }

    hc.assign(n + 1, std::string{});
    for (int i = 1; i <= n; ++i) {
        std::string cd;
        int c = i;
        int f = ht[i].parent;
        while (f != 0) {
            cd.push_back(ht[f].lchild == c ? '0' : '1');
            c = f;
            f = ht[f].parent;
        }
        std::reverse(cd.begin(), cd.end());
        hc[i] = cd;
    }

    return OK;
}

int main() {
    std::vector<char> symbols = {'A', 'B', 'C', 'D', 'E', 'F'};
    std::vector<unsigned int> weights = {5, 9, 12, 13, 16, 45};

    HuffmanTree ht;
    HuffmanCode hc;

    Status st = HuffmanCoding(ht, hc, weights);
    std::cout << "Status=" << (st == OK ? "OK" : "ERROR") << '\n';
    if (st != OK) return 0;

    std::cout << "HuffmanCodes:\n";
    for (int i = 1; i <= static_cast<int>(symbols.size()); ++i) {
        std::cout << symbols[i - 1] << "(" << weights[i - 1] << "):" << hc[i] << '\n';
    }
    return 0;
}

