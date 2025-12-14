from __future__ import annotations

from datetime import date
from pathlib import Path

from docx import Document


def main() -> None:
    here = Path(__file__).resolve().parent
    report_path = here.parent / "实验报告.docx"
    code_path = here / "exp07.cpp"
    output_path = here / "exp07_output.txt"
    experiment_title = "实验名称：图的深度优先遍历（DFSTraverse）"

    doc = Document(str(report_path))
    row = doc.tables[0].rows[3]
    old = row.cells[0].text.rstrip()
    if experiment_title in old:
        print("skip: exp07 already injected")
        return

    run_output = output_path.read_text(encoding="utf-8").rstrip()
    code = code_path.read_text(encoding="utf-8").rstrip()

    block = "\n".join(
        [
            experiment_title,
            f"实验时间：{date.today().isoformat()}",
            r"实验地点：E:\cpp 本机",
            "实验内容：在邻接表存储的图上实现深度优先遍历。通过 visited 数组标记访问状态，对每个未访问顶点调用 DFS。",
            "实验步骤：",
            "1) 初始化 visited[0..vexnum-1] 为 FALSE；",
            "2) 依次扫描顶点 v，若 v 未访问则调用 DFS(G, v)；",
            "3) DFS：置 visited[v]=TRUE 并 Visit(v)；",
            "4) 沿 v 的邻接表逐个访问邻接点 w，若 w 未访问则递归 DFS(G, w)。",
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
