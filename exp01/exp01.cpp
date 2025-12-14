#include <bits/stdc++.h>
using namespace std;

const int LISTINCREMENT = 10;

// 最简：顺序表插入，手动扩容并搬移元素
bool ListInsert_Sq(vector<int> &elem, int &length, int &listsize, int i, int e) {
    if (i < 1 || i > length + 1) return false;
    if (length >= listsize) { // 需要扩容
        listsize += LISTINCREMENT;
        elem.resize(listsize);
    }
    int q = i - 1; // 插入位置下标
    for (int p = length - 1; p >= q; --p) elem[p + 1] = elem[p];
    elem[q] = e;
    ++length;
    return true;
}

int main() {
    vector<int> elem(5);
    int listsize = 5, length = 3;
    elem[0] = 1; elem[1] = 3; elem[2] = 4;

    ListInsert_Sq(elem, length, listsize, 2, 2);

    for (int k = 0; k < length; ++k) {
        if (k) cout << ' ';
        cout << elem[k];
    }
    cout << '\n';
    return 0;
}
