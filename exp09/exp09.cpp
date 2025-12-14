#include <iostream>
#include <vector>

struct ElemType {
    int key = 0;
};

struct SqList {
    std::vector<ElemType> r;  // 从 1 开始编号
    int length = 0;
};

int Partition(SqList& l, int low, int high) {
    int pivotkey = l.r[low].key;
    while (low < high) {
        while (low < high && l.r[high].key >= pivotkey) --high;
        l.r[low] = l.r[high];
        while (low < high && l.r[low].key <= pivotkey) ++low;
        l.r[high] = l.r[low];
    }
    l.r[low].key = pivotkey;
    return low;
}

void QSort(SqList& l, int low, int high) {
    if (low < high) {
        int pivotloc = Partition(l, low, high);
        QSort(l, low, pivotloc - 1);
        QSort(l, pivotloc + 1, high);
    }
}

void QuickSort(SqList& l) { QSort(l, 1, l.length); }

void printList(const SqList& l) {
    for (int i = 1; i <= l.length; ++i) {
        if (i != 1) std::cout << ' ';
        std::cout << l.r[i].key;
    }
    std::cout << '\n';
}

int main() {
    std::vector<int> keys = {49, 38, 65, 97, 76, 13, 27, 49};
    SqList l;
    l.length = static_cast<int>(keys.size());
    l.r.assign(l.length + 1, ElemType{});
    for (int i = 1; i <= l.length; ++i) l.r[i].key = keys[i - 1];

    std::cout << "Original:";
    for (int k : keys) std::cout << ' ' << k;
    std::cout << '\n';

    QuickSort(l);

    std::cout << "Sorted:";
    for (int i = 1; i <= l.length; ++i) std::cout << ' ' << l.r[i].key;
    std::cout << '\n';
    return 0;
}

