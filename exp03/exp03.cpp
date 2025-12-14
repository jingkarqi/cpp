#include <cstdlib>
#include <iostream>

using SElemType = int;

constexpr int STACK_INIT_SIZE = 100;

enum Status { OK = 1, ERROR = 0 };

struct SqStack {
    SElemType* base = nullptr;
    SElemType* top = nullptr;
    int stacksize = 0;
};

Status InitStack(SqStack& s) {
    s.base = static_cast<SElemType*>(std::malloc(STACK_INIT_SIZE * sizeof(SElemType)));
    if (!s.base) std::exit(1);
    s.top = s.base;
    s.stacksize = STACK_INIT_SIZE;
    return OK;
}

bool isEmpty(const SqStack& s) { return s.top == s.base; }
int stackLength(const SqStack& s) { return static_cast<int>(s.top - s.base); }

Status Push(SqStack& s, SElemType e) {
    if (stackLength(s) >= s.stacksize) return ERROR;
    *s.top++ = e;
    return OK;
}

Status Pop(SqStack& s, SElemType& e) {
    if (isEmpty(s)) return ERROR;
    e = *--s.top;
    return OK;
}

int main() {
    SqStack s;
    Status st = InitStack(s);

    std::cout << "InitStack=" << (st == OK ? "OK" : "ERROR") << '\n';
    std::cout << "stacksize=" << s.stacksize << '\n';
    std::cout << "empty=" << (isEmpty(s) ? 1 : 0) << '\n';

    Push(s, 7);
    Push(s, 8);
    std::cout << "length_after_push=" << stackLength(s) << '\n';

    SElemType x = 0;
    Pop(s, x);
    std::cout << "pop=" << x << '\n';
    std::cout << "length_end=" << stackLength(s) << '\n';

    std::free(s.base);
    return 0;
}
