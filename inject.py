from docx import Document

report_path = r"E:\\cpp\\实验报告.docx"
text = """实验内容：
1. 线性表顺序存储插入（ListInsert_Sq）。
2. 初始条件：顺序表 L 存在，1≤i≤ListLength_Sq(L)+1。
3. 任务：在第 i 个位置插入元素 e，若存储已满则扩容 LISTINCREMENT。

实验步骤：
1) 判断 i 是否在合法区间，否则返回 ERROR。
2) 若 L.length >= L.listsize，申请新空间并更新基址与容量。
3) 定位插入位置指针 q = &L.elem[i-1]。
4) 从表尾向前移动元素，空出插入位置。
5) *q = e；L.length++；返回 OK。

伪代码：
Status ListInsert_Sq(SqList &L, int i, ElemType e) {
    // 初始条件：线性表L存在，1≤i≤ListLength_Sq(L)+1
    if (i < 1 || i > L.length + 1) return ERROR; // i值不合法
    if (L.length >= L.listsize) { // 当前存储空间已满，增加分配
        ElemType *newbase = (ElemType *)realloc(L.elem, 
            (L.listsize + LISTINCREMENT) * sizeof(ElemType));
        if (!newbase) exit(OVERFLOW); // 存储分配失败
        L.elem = newbase; // 更新基址
        L.listsize += LISTINCREMENT; // 增加存储容量
    }
    ElemType *q = &(L.elem[i - 1]); // q指向插入位置
    for (ElemType *p = &(L.elem[L.length - 1]); p >= q; --p) {
        *(p + 1) = *p; // 插入位置及之后元素向后移1位
    }
    *q = e; // 插入新元素e
    ++L.length; // 表长增1
    return OK;
}

C++参考实现：
#include <bits/stdc++.h>
using namespace std;

struct SqList {
    vector<int> elem;
    int length = 0;
    int listsize = 0;
};

const int LISTINCREMENT = 10;

bool ListInsert_Sq(SqList &L, int i, int e) {
    if (i < 1 || i > L.length + 1) return false;
    if (L.length >= L.listsize) {
        L.listsize += LISTINCREMENT;
        L.elem.resize(L.listsize);
    }
    int q = i - 1;
    for (int p = L.length - 1; p >= q; --p) L.elem[p + 1] = L.elem[p];
    if (q >= (int)L.elem.size()) L.elem.resize(q + 1);
    L.elem[q] = e;
    ++L.length;
    return true;
}

int main() {
    SqList L; L.listsize = 5; L.elem.resize(L.listsize);
    L.elem[0]=1; L.elem[1]=3; L.elem[2]=4; L.length=3;

    ListInsert_Sq(L, 2, 2); // 插入位置2 元素2
    for (int k=0;k<L.length;++k) cout << L.elem[k] << (k+1==L.length?'\\n':' ');
    return 0;
}
"""

doc = Document(report_path)
row = doc.tables[0].rows[3]
for cell in row.cells:
    cell.text = text

doc.save(report_path)
print("updated")
