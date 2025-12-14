from docx import Document

txt = """实验名称：顺序表插入算法的实现
实验时间：2025-12-14
实验地点：E\\cpp 本机
实验内容：实现顺序表（基于动态数组）的插入功能。当向顺序表的指定位置插入新元素时，若当前存储空间已满，则自动扩容。通过本实验理解顺序表的存储结构、插入操作的基本步骤以及动态扩容机制。
实验步骤：
定义顺序表结构：使用 vector<int> 作为底层存储，用 length 记录当前元素个数，listsize 记录当前总容量。
编写插入函数 ListInsert_Sq：
判断插入位置 i 是否合法。
若 length >= listsize，则扩容（增加 LISTINCREMENT 个单位）。
将插入位置及之后的元素依次后移一位。
插入新元素，并更新 length。
编写主函数进行测试：
初始化一个顺序表，初始内容为 [1, 3, 4]。
调用插入函数，在位置 2 插入元素 2。
输出插入后的顺序表内容。
源代码：
#include <bits/stdc++.h>
using namespace std;
const int LISTINCREMENT = 10;
bool ListInsert_Sq(vector<int>& elem, int& length, int& listsize, int i, int e) {
    if (i < 1 || i > length + 1) return false;
    if (length >= listsize) { listsize += LISTINCREMENT; elem.resize(listsize); }
    int q = i - 1;
    for (int p = length - 1; p >= q; --p) elem[p + 1] = elem[p];
    elem[q] = e; ++length; return true;
}
int main() {
    vector<int> elem(5); int listsize = 5, length = 3; elem[0]=1; elem[1]=3; elem[2]=4;
    ListInsert_Sq(elem, length, listsize, 2, 2);
    for (int k=0; k<length; ++k) { if (k) cout << ' '; cout << elem[k]; }
    cout << '\\n'; return 0;
}
实验结果：程序运行输出：1 2 3 4，成功在位置 2 插入元素 2，得到 [1, 2, 3, 4]。
源文件：E\\cpp\\ListInsert_Sq.cpp
"""

src = r"E:\\cpp\\实验报告.docx"
out = r"E:\\cpp\\实验报告.docx"

doc = Document(src)
row = doc.tables[0].rows[3]
for cell in row.cells:
    cell.text = txt

doc.save(out)
print('updated', out)
