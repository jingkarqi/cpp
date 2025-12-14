from __future__ import annotations

from datetime import date
from pathlib import Path

from docx import Document


def main() -> None:
    here = Path(__file__).resolve().parent
    report_path = here.parent / "实验报告.docx"
    code_path = here / "exp09.cpp"
    output_path = here / "exp09_output.txt"
    experiment_title = "实验名称：快速排序划分（Partition / QuickSort）"

    doc = Document(str(report_path))
    row = doc.tables[0].rows[3]
    old = row.cells[0].text.rstrip()
    if experiment_title in old:
        print("skip: exp09 already injected")
        return

    run_output = output_path.read_text(encoding="utf-8").rstrip()
    code = code_path.read_text(encoding="utf-8").rstrip()

    block = "\n".join(
        [
            experiment_title,
            f"实验时间：{date.today().isoformat()}",
            r"实验地点：E:\cpp 本机",
            "实验内容：实现快速排序的划分函数 Partition，并在此基础上完成 QuickSort。划分选取第一个元素为枢轴，通过双指针从两端向中间扫描。",
            "实验步骤：",
            "1) pivotkey = r[low].key，选择首元素为枢轴；",
            "2) high 从右向左找 < pivotkey 的元素，放到 low 位置；",
            "3) low 从左向右找 > pivotkey 的元素，放到 high 位置；",
            "4) low==high 时将 pivotkey 放回最终位置并返回枢轴下标；",
            "5) QSort 递归排序枢轴左右子区间。",
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
