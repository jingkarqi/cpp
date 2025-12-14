from docx import Document

text = r"""实验名称：顺序表插入（ListInsert_Sq）
实验时间：2025-12-14
实验地点：E:\\cpp 本机
实验内容：在顺序表第 i 个位置插入元素；当 length >= listsize 时先扩容 LISTINCREMENT 再插入。
实验步骤：
1) 检查 i 是否在 [1, length+1]；
2) 如需扩容则调整 listsize 并扩展顺序表；
3) 设 q = i-1；
4) 自表尾向前搬移元素，为插入腾位；
5) 置 L[q]=e，length++。
实验结果：编译并运行 `ListInsert_Sq.cpp`（g++ 15.2.0），输出：1 2 3 4。
源文件：E:\\cpp\\ListInsert_Sq.cpp
"""

src = r"E:\\cpp\\实验报告.docx"
out = r"E:\\cpp\\实验报告_填充.docx"
doc = Document(src)
row = doc.tables[0].rows[3]
for cell in row.cells:
    cell.text = text

doc.save(out)
print("saved", out)
