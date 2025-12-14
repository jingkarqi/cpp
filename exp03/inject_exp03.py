from __future__ import annotations

from datetime import date
from pathlib import Path

from docx import Document


def main() -> None:
    here = Path(__file__).resolve().parent
    report_path = here.parent / "实验报告.docx"
    code_path = here / "exp03.cpp"
    output_path = here / "exp03_output.txt"
    experiment_title = "实验名称：顺序栈初始化（InitStack）"

    doc = Document(str(report_path))
    row = doc.tables[0].rows[3]
    old = row.cells[0].text.rstrip()
    if experiment_title in old:
        print("skip: exp03 already injected")
        return

    run_output = output_path.read_text(encoding="utf-8").rstrip()
    code = code_path.read_text(encoding="utf-8").rstrip()

    block = "\n".join(
        [
            experiment_title,
            f"实验时间：{date.today().isoformat()}",
            r"实验地点：E:\cpp 本机",
            "实验内容：实现顺序栈（顺序存储结构）的初始化操作，理解 base/top 指针与 stacksize 的含义。",
            "实验步骤：",
            "1) 申请 STACK_INIT_SIZE 个 SElemType 的连续存储空间作为栈底 base；",
            "2) 若分配失败则终止程序；",
            "3) 令 top = base 表示空栈；",
            "4) 置 stacksize = STACK_INIT_SIZE；返回 OK。",
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
