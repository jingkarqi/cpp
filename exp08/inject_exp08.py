from __future__ import annotations

from datetime import date
from pathlib import Path

from docx import Document


def main() -> None:
    here = Path(__file__).resolve().parent
    report_path = here.parent / "实验报告.docx"
    code_path = here / "exp08.cpp"
    output_path = here / "exp08_output.txt"
    experiment_title = "实验名称：Dijkstra最短路径（ShortestPath_DIJ）"

    doc = Document(str(report_path))
    row = doc.tables[0].rows[3]
    old = row.cells[0].text.rstrip()
    if experiment_title in old:
        print("skip: exp08 already injected")
        return

    run_output = output_path.read_text(encoding="utf-8").rstrip()
    code = code_path.read_text(encoding="utf-8").rstrip()

    block = "\n".join(
        [
            experiment_title,
            f"实验时间：{date.today().isoformat()}",
            r"实验地点：E:\cpp 本机",
            "实验内容：在邻接矩阵表示的有向网中实现 Dijkstra 算法，求源点 v0 到其余各顶点的最短路径长度。",
            "实验步骤：",
            "1) 初始化：D[v]=arcs[v0][v]；final[v]=FALSE；若有直接弧则在 P 中标记 v0 与 v；",
            "2) 置 D[v0]=0，final[v0]=TRUE；",
            "3) 重复 n-1 次：在未确定的顶点中选 D 最小者 u，置 final[u]=TRUE；",
            "4) 用 u 松弛其余顶点 v：若 D[u]+arcs[u][v] < D[v]，则更新 D[v] 并更新路径信息。",
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
