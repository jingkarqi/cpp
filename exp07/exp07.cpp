#include <iostream>
#include <vector>

enum Status { OK = 1, ERROR = 0 };

struct ArcNode {
    int adjvex;
    ArcNode* nextarc;
};

struct VexNode {
    char data;
    ArcNode* firstarc = nullptr;
};

struct ALGraph {
    std::vector<VexNode> vertices;
    int vexnum = 0;
    int arcnum = 0;
    bool directed = false;
};

std::vector<bool> visited;
std::vector<char> labels;
bool firstOut = true;

Status Visit(int v) {
    if (!firstOut) std::cout << ' ';
    std::cout << labels[v];
    firstOut = false;
    return OK;
}

void appendArc(ALGraph& g, int from, int to) {
    auto* node = new ArcNode{to, nullptr};
    ArcNode*& head = g.vertices[from].firstarc;
    if (!head) {
        head = node;
        return;
    }
    ArcNode* p = head;
    while (p->nextarc) p = p->nextarc;
    p->nextarc = node;
}

void addEdgeUndirected(ALGraph& g, int u, int v) {
    appendArc(g, u, v);
    appendArc(g, v, u);
    g.arcnum += 2;
}

void DFS(const ALGraph& g, int v, Status (*visit)(int v)) {
    visited[v] = true;
    visit(v);
    for (ArcNode* p = g.vertices[v].firstarc; p; p = p->nextarc) {
        int w = p->adjvex;
        if (!visited[w]) DFS(g, w, visit);
    }
}

void DFSTraverse(const ALGraph& g, Status (*visit)(int v)) {
    visited.assign(g.vexnum, false);
    for (int v = 0; v < g.vexnum; ++v) {
        if (!visited[v]) DFS(g, v, visit);
    }
}

void freeGraph(ALGraph& g) {
    for (auto& vex : g.vertices) {
        ArcNode* p = vex.firstarc;
        while (p) {
            ArcNode* next = p->nextarc;
            delete p;
            p = next;
        }
        vex.firstarc = nullptr;
    }
}

int main() {
    // 顶点：A B C D E F G（G为孤立点）
    labels = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    ALGraph g;
    g.vexnum = static_cast<int>(labels.size());
    g.vertices.resize(g.vexnum);
    for (int i = 0; i < g.vexnum; ++i) g.vertices[i].data = labels[i];

    // 无向图边：A-B, A-C, B-D, B-E, C-F
    addEdgeUndirected(g, 0, 1);
    addEdgeUndirected(g, 0, 2);
    addEdgeUndirected(g, 1, 3);
    addEdgeUndirected(g, 1, 4);
    addEdgeUndirected(g, 2, 5);

    std::cout << "DFSTraverse:";
    firstOut = true;
    DFSTraverse(g, Visit);
    std::cout << '\n';

    freeGraph(g);
    return 0;
}

