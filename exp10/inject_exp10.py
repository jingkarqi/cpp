from __future__ import annotations

from datetime import date
from pathlib import Path

from docx import Document


def main() -> None:
    here = Path(__file__).resolve().parent
    report_path = here.parent / "实验报告.docx"
    code_path = here / "exp10.cpp"
    output_path = here / "exp10_output.txt"
    experiment_title = "实验名称：置换选择生成初始归并段（Replace_Selection）"

    doc = Document(str(report_path))
    row = doc.tables[0].rows[3]
    old = row.cells[0].text.rstrip()
    if experiment_title in old:
        print("skip: exp10 already injected")
        return

    run_output = output_path.read_text(encoding="utf-8").rstrip()
    code = code_path.read_text(encoding="utf-8").rstrip()

    block = "\n".join(
        [
            experiment_title,
            f"实验时间：{date.today().isoformat()}",
            r"实验地点：E:\cpp 本机",
            "实验内容：使用置换选择（Replacement Selection）在容量为 w 的内存工作区内生成初始归并段；通过败者树（LoserTree）快速选出当前段的 MINIMAX 记录。",
            "实验步骤：",
            "1) 读入 w 个记录到工作区，段号 rnum 置为 1，并构建败者树；",
            "2) 反复输出败者树根所指向的关键字最小记录（MINIMAX）；",
            "3) 用新读入记录替换被输出位置：若新关键字 < minimax，则该记录归入新段（段号递增），否则归入当前段；",
            "4) 调整败者树，更新根并据此更新当前段号；",
            "5) 输入耗尽后输出段结束标志（INF）。",
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
