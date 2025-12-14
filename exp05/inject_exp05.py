from __future__ import annotations

from datetime import date
from pathlib import Path

from docx import Document


def main() -> None:
    here = Path(__file__).resolve().parent
    report_path = here.parent / "实验报告.docx"
    code_path = here / "exp05.cpp"
    output_path = here / "exp05_output.txt"
    experiment_title = "实验名称：二叉树先序遍历（PreOrderTraverse）"

    doc = Document(str(report_path))
    row = doc.tables[0].rows[3]
    old = row.cells[0].text.rstrip()
    if experiment_title in old:
        print("skip: exp05 already injected")
        return

    run_output = output_path.read_text(encoding="utf-8").rstrip()
    code = code_path.read_text(encoding="utf-8").rstrip()

    block = "\n".join(
        [
            experiment_title,
            f"实验时间：{date.today().isoformat()}",
            r"实验地点：E:\cpp 本机",
            "实验内容：实现二叉树先序遍历。遍历顺序为：根结点 → 左子树 → 右子树；空树遍历视为成功。",
            "实验步骤：",
            "1) 若 T 为空，返回 OK；",
            "2) 访问根结点：Visit(T->data)；",
            "3) 递归遍历左子树：PreOrderTraverse(T->lchild, Visit)；",
            "4) 递归遍历右子树：PreOrderTraverse(T->rchild, Visit)；",
            "5) 三步均成功则返回 OK，否则返回 ERROR。",
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
