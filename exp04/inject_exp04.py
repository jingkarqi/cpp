from __future__ import annotations

from datetime import date
from pathlib import Path

from docx import Document


def main() -> None:
    here = Path(__file__).resolve().parent
    report_path = here.parent / "实验报告.docx"
    code_path = here / "exp04.cpp"
    output_path = here / "exp04_output.txt"
    experiment_title = "实验名称：循环队列入队（EnQueue_Sq）"

    doc = Document(str(report_path))
    row = doc.tables[0].rows[3]
    old = row.cells[0].text.rstrip()
    if experiment_title in old:
        print("skip: exp04 already injected")
        return

    run_output = output_path.read_text(encoding="utf-8").rstrip()
    code = code_path.read_text(encoding="utf-8").rstrip()

    block = "\n".join(
        [
            experiment_title,
            f"实验时间：{date.today().isoformat()}",
            r"实验地点：E:\cpp 本机",
            "实验内容：实现循环队列的入队操作。队列用 base 数组存储，front 指向队头元素，rear 指向队尾元素的下一个位置。",
            "实验步骤：",
            "1) 判断队满：若 (rear+1)%MAXQSIZE == front，则返回 ERROR；",
            "2) 将元素 e 写入 base[rear]；",
            "3) rear = (rear+1)%MAXQSIZE，尾指针循环后移；",
            "4) 返回 OK。",
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
