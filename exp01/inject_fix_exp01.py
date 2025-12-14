from __future__ import annotations

from pathlib import Path

from docx import Document


def main() -> None:
    here = Path(__file__).resolve().parent
    report_path = here.parent / "实验报告.docx"
    src_line = r"源文件：E:\cpp\exp01\exp01.cpp"
    marker = "实验名称：单链表按位查找算法的实现"

    doc = Document(str(report_path))
    row = doc.tables[0].rows[3]
    old = row.cells[0].text

    if src_line in old:
        print("skip: exp01 source already present")
        return

    if marker not in old:
        raise SystemExit(f"cannot find marker: {marker}")

    new_text = old.replace("\n\n" + marker, "\n" + src_line + "\n\n" + marker, 1)
    for cell in row.cells:
        cell.text = new_text

    doc.save(str(report_path))
    print("updated", report_path)


if __name__ == "__main__":
    main()
