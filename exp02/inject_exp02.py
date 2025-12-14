from __future__ import annotations

from datetime import date
from pathlib import Path

from docx import Document


def main() -> None:
    here = Path(__file__).resolve().parent
    report_path = here.parent / "实验报告.docx"
    code_path = here / "exp02.cpp"
    output_path = here / "exp02_output.txt"

    block = "\n".join(
        [
            "实验名称：单链表按位查找算法的实现",
            f"实验时间：{date.today().isoformat()}",
            r"实验地点：E\cpp 本机",
            "实验内容：在带头结点的单链表中查找第 i 个元素，用 e 返回该元素值；理解链表遍历与越界判断。",
            "实验步骤：",
            "初始化：构造带头结点的单链表，令 p 指向首元结点 L->next，j=1。",
            "循环：当 p 非空且 j<i 时，p 后移到下一个结点并 ++j。",
            "判定：若 p 为空或 j>i，则第 i 个结点不存在，返回 ERROR。",
            "返回：否则令 e=p->data，返回 OK。",
            "源代码：",
            "",
            "实验结果：",
            "程序运行后输出结果为：",
            "",
            rf"源文件：{code_path}",
        ]
    )

    doc = Document(str(report_path))
    row = doc.tables[0].rows[3]
    old = row.cells[0].text.rstrip()
    if "实验名称：单链表按位查找算法的实现" in old:
        print("skip: exp02 already injected")
        return

    run_output = output_path.read_text(encoding="utf-8").rstrip()
    code = code_path.read_text(encoding="utf-8").rstrip()

    block = block.replace("\n\n实验结果：\n程序运行后输出结果为：\n\n", "\n\n实验结果：\n程序运行后输出结果为：\n" + run_output + "\n", 1)
    block = block.replace("\n\n实验步骤：\n", "\n\n实验步骤：\n", 1)
    block = block.replace("\n\n源代码：\n\n", "\n\n源代码：\n" + code + "\n", 1)

    new_text = (old + "\n\n" + block) if old else block
    for cell in row.cells:
        cell.text = new_text

    doc.save(str(report_path))
    print("updated", report_path)


if __name__ == "__main__":
    main()
