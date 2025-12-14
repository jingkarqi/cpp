#include <iostream>
#include <vector>

struct LNode {
    int data;
    LNode* next;
};

using LinkList = LNode*;

enum Status { OK = 1, ERROR = 0 };

Status GetElem_L(LinkList L, int i, int& e) {
    if (!L || i < 1) return ERROR;
    LinkList p = L->next;
    int j = 1;
    while (p && j < i) {
        p = p->next;
        ++j;
    }
    if (!p || j > i) return ERROR;
    e = p->data;
    return OK;
}

LinkList buildListWithHead(const std::vector<int>& values) {
    auto* head = new LNode{0, nullptr};
    LNode* tail = head;
    for (int v : values) {
        tail->next = new LNode{v, nullptr};
        tail = tail->next;
    }
    return head;
}

void freeList(LinkList L) {
    while (L) {
        LNode* next = L->next;
        delete L;
        L = next;
    }
}

int main() {
    LinkList L = buildListWithHead({10, 20, 30, 40});

    std::cout << "List:";
    for (LNode* p = L->next; p; p = p->next) std::cout << ' ' << p->data;
    std::cout << '\n';

    int e = 0;
    for (int i : {3, 5}) {
        if (GetElem_L(L, i, e) == OK) {
            std::cout << "GetElem_L(" << i << ")=" << e << '\n';
        } else {
            std::cout << "GetElem_L(" << i << ")=ERROR\n";
        }
    }

    freeList(L);
    return 0;
}
