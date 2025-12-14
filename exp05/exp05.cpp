#include <iostream>

using TElemType = char;

enum Status { OK = 1, ERROR = 0 };

struct BiTNode {
    TElemType data;
    BiTNode* lchild;
    BiTNode* rchild;
};

using BiTree = BiTNode*;

bool firstOut = true;

Status Visit(TElemType e) {
    if (!firstOut) std::cout << ' ';
    std::cout << e;
    firstOut = false;
    return OK;
}

Status PreOrderTraverse(BiTree t, Status (*visit)(TElemType)) {
    if (t) {
        if (visit(t->data))
            if (PreOrderTraverse(t->lchild, visit))
                if (PreOrderTraverse(t->rchild, visit)) return OK;
        return ERROR;
    }
    return OK;
}

BiTree node(TElemType data, BiTree l = nullptr, BiTree r = nullptr) {
    return new BiTNode{data, l, r};
}

void freeTree(BiTree t) {
    if (!t) return;
    freeTree(t->lchild);
    freeTree(t->rchild);
    delete t;
}

int main() {
    //      A
    //    /   \
    //   B     C
    //  / \     \
    // D   E     F
    BiTree t = node('A', node('B', node('D'), node('E')), node('C', nullptr, node('F')));

    std::cout << "PreOrder:";
    firstOut = true;
    Status st = PreOrderTraverse(t, Visit);
    std::cout << '\n';
    std::cout << "Status=" << (st == OK ? "OK" : "ERROR") << '\n';

    freeTree(t);

    // 空树
    std::cout << "EmptyTree:";
    firstOut = true;
    std::cout << '\n';
    std::cout << "Status=" << (PreOrderTraverse(nullptr, Visit) == OK ? "OK" : "ERROR") << '\n';
    return 0;
}

