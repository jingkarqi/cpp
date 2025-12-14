#include <cstdlib>
#include <iostream>

using QElemType = int;

constexpr int MAXQSIZE = 100;

enum Status { OK = 1, ERROR = 0 };

struct SqQueue {
    QElemType* base = nullptr;
    int front = 0;
    int rear = 0;
};

Status InitQueue(SqQueue& q) {
    q.base = static_cast<QElemType*>(std::malloc(MAXQSIZE * sizeof(QElemType)));
    if (!q.base) std::exit(1);
    q.front = q.rear = 0;
    return OK;
}

int queueLength(const SqQueue& q) { return (q.rear - q.front + MAXQSIZE) % MAXQSIZE; }

Status EnQueue_Sq(SqQueue& q, QElemType e) {
    if ((q.rear + 1) % MAXQSIZE == q.front) return ERROR;
    q.base[q.rear] = e;
    q.rear = (q.rear + 1) % MAXQSIZE;
    return OK;
}

Status DeQueue_Sq(SqQueue& q, QElemType& e) {
    if (q.front == q.rear) return ERROR;
    e = q.base[q.front];
    q.front = (q.front + 1) % MAXQSIZE;
    return OK;
}

void printQueue(const SqQueue& q) {
    std::cout << "queue:";
    for (int i = 0, cur = q.front; i < queueLength(q); ++i, cur = (cur + 1) % MAXQSIZE) {
        std::cout << ' ' << q.base[cur];
    }
    std::cout << '\n';
}

int main() {
    SqQueue q;
    std::cout << "InitQueue=" << (InitQueue(q) == OK ? "OK" : "ERROR") << '\n';

    for (int v : {10, 20, 30}) {
        std::cout << "EnQueue(" << v << ")=" << (EnQueue_Sq(q, v) == OK ? "OK" : "ERROR") << '\n';
    }
    std::cout << "length=" << queueLength(q) << '\n';

    int x = 0;
    if (DeQueue_Sq(q, x) == OK) std::cout << "DeQueue=" << x << '\n';

    for (int v : {40, 50}) {
        std::cout << "EnQueue(" << v << ")=" << (EnQueue_Sq(q, v) == OK ? "OK" : "ERROR") << '\n';
    }

    printQueue(q);
    std::cout << "front=" << q.front << " rear=" << q.rear << '\n';

    std::free(q.base);
    return 0;
}

