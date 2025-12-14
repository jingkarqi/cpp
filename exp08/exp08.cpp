#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

constexpr int INFINITY = INT_MAX;

using PathMatrix = std::vector<std::vector<bool>>;
using ShortPathTable = std::vector<int>;

struct MGraph {
    std::vector<char> vexs;
    std::vector<std::vector<int>> arcs;
    int vexnum = 0;
    int arcnum = 0;
};

void ShortestPath_DIJ(const MGraph& g, int v0, PathMatrix& p, ShortPathTable& d, std::vector<int>& prev) {
    const int n = g.vexnum;
    std::vector<bool> final(n, false);
    p.assign(n, std::vector<bool>(n, false));
    d.assign(n, INFINITY);
    prev.assign(n, -1);

    for (int v = 0; v < n; ++v) {
        final[v] = false;
        d[v] = g.arcs[v0][v];
        if (d[v] < INFINITY) {
            p[v][v0] = true;
            p[v][v] = true;
            prev[v] = v0;
        }
    }
    d[v0] = 0;
    p[v0][v0] = true;
    prev[v0] = v0;
    final[v0] = true;

    for (int i = 1; i < n; ++i) {
        int u = -1;
        int min = INFINITY;
        for (int v = 0; v < n; ++v) {
            if (!final[v] && d[v] < min) {
                u = v;
                min = d[v];
            }
        }
        if (u == -1 || min == INFINITY) break;
        final[u] = true;

        for (int v = 0; v < n; ++v) {
            if (final[v]) continue;
            if (g.arcs[u][v] == INFINITY) continue;
            long long alt = static_cast<long long>(min) + g.arcs[u][v];
            if (alt < d[v]) {
                d[v] = static_cast<int>(alt);
                p[v] = p[u];
                p[v][v] = true;
                prev[v] = u;
            }
        }
    }
}

std::vector<int> buildPath(int v0, int v, const std::vector<int>& prev) {
    std::vector<int> path;
    if (v < 0 || v >= static_cast<int>(prev.size())) return path;
    if (prev[v] == -1) return path;

    int cur = v;
    while (cur != v0) {
        path.push_back(cur);
        cur = prev[cur];
        if (cur == -1) return {};
    }
    path.push_back(v0);
    std::reverse(path.begin(), path.end());
    return path;
}

int main() {
    // 示例有向网：A,B,C,D,E
    // A->B 10, A->C 3
    // B->C 1, B->D 2
    // C->B 4, C->D 8, C->E 2
    // D->E 7
    // E->D 9
    MGraph g;
    g.vexs = {'A', 'B', 'C', 'D', 'E'};
    g.vexnum = static_cast<int>(g.vexs.size());
    g.arcs.assign(g.vexnum, std::vector<int>(g.vexnum, INFINITY));
    for (int i = 0; i < g.vexnum; ++i) g.arcs[i][i] = 0;

    auto addArc = [&](int u, int v, int w) {
        g.arcs[u][v] = w;
        ++g.arcnum;
    };
    addArc(0, 1, 10);
    addArc(0, 2, 3);
    addArc(1, 2, 1);
    addArc(1, 3, 2);
    addArc(2, 1, 4);
    addArc(2, 3, 8);
    addArc(2, 4, 2);
    addArc(3, 4, 7);
    addArc(4, 3, 9);

    PathMatrix p;
    ShortPathTable d;
    std::vector<int> prev;
    const int v0 = 0;
    ShortestPath_DIJ(g, v0, p, d, prev);

    std::cout << "DijkstraFrom=" << g.vexs[v0] << '\n';
    for (int v = 0; v < g.vexnum; ++v) {
        std::cout << g.vexs[v] << ":";
        if (d[v] == INFINITY) {
            std::cout << "INF\n";
            continue;
        }
        std::cout << d[v] << " path:";
        auto path = buildPath(v0, v, prev);
        for (int idx : path) std::cout << ' ' << g.vexs[idx];
        std::cout << '\n';
    }
    return 0;
}

