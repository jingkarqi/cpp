from __future__ import annotations

from datetime import date
from pathlib import Path

from docx import Document


def main() -> None:
    here = Path(__file__).resolve().parent
    report_path = here.parent / "实验报告.docx"
    code_path = here / "exp06.cpp"
    output_path = here / "exp06_output.txt"
    experiment_title = "实验名称：赫夫曼编码（HuffmanCoding）"

    doc = Document(str(report_path))
    row = doc.tables[0].rows[3]
    old = row.cells[0].text.rstrip()
    if experiment_title in old:
        print("skip: exp06 already injected")
        return

    run_output = output_path.read_text(encoding="utf-8").rstrip()
    code = code_path.read_text(encoding="utf-8").rstrip()

    block = "\n".join(
        [
            experiment_title,
            f"实验时间：{date.today().isoformat()}",
            r"实验地点：E:\cpp 本机",
            "实验内容：根据给定的 n 个权值构造赫夫曼树，并生成每个叶子结点的赫夫曼编码（左分支记 0，右分支记 1）。",
            "实验步骤：",
            "1) 初始化前 n 个叶子结点，parent/lchild/rchild 均置 0；",
            "2) 对 i=n+1..m(=2n-1)：在 1..i-1 中选择两个 parent=0 且权值最小的结点 s1、s2；",
            "3) 令 s1、s2 的 parent=i，设置 i 的左右孩子并累加权值；",
            "4) 对每个叶子结点从该结点回溯到根：左孩子记 0，右孩子记 1，反向得到编码。",
            "源代码：",
            code,
            "实验结果：",
            "程序运行后输出结果为：",
            run_output,
            rf"源文件：{code_path}",
        ]
    )

    new_text = (old + "\n\n" + block) if old else block
    for cell in row.cells:
        cell.text = new_text

    doc.save(str(report_path))
    print("updated", report_path)


if __name__ == "__main__":
    main()
