# Troubleshooting Notes (2025-12-14)

- PowerShell heredoc `python - <<'PY'` is a Bash-only syntax; use PowerShell here-strings (`@'...'@ | python -`) or `python -c` instead, otherwise it errors with “Missing file specification after redirection operator.”
- Early `pip` calls failed because `python-docx` was not installed and `pip` was not on PATH; resolved by installing `python-docx` and using `python -m pip ...`.
- `npm install docx` initially hit EPERM due to default cache permissions; succeeded after specifying a writable cache (`--cache E:\\cpp\\npm-cache`).
- A one-time Windows popup (0xc0000142) appeared during earlier Python starts, likely from those failed/blocked invocations; subsequent `python -c "print('ok')"` runs cleanly.
- Policy: when new packages are required, pause work and surface the exact install command for the user to run; resume only after the user replies “继续”/“continue”.

## DOCX edit workflow（实验报告.docx）
- 让用户先安装依赖：`python -m pip install python-docx`（提示后等待确认再继续）。
- 检查结构：`python -c "from docx import Document; doc=Document(r'E:\\cpp\\实验报告.docx'); print('paras',len(doc.paragraphs)); print('tables',len(doc.tables))"`。
- 该封面只有 1 个表格；`rows[3]` 是“实验内容”整块，所有 8 个单元格内容相同，可直接对该行循环设置 `cell.text = base + '\n\n' + cpp_code`。
- 长脚本写法：用 PowerShell here-string 写入临时 `inject.py`，再 `python inject.py`，避免复杂转义；示例见本次 `inject.py` 流程。
- 追加代码示例后可验证：`python -c "from docx import Document; print(Document(r'E:\\cpp\\实验报告.docx').tables[0].rows[3].cells[0].text)"` 确认文本落盘。

## 实验报告填充工作流（对标“实验报告-范例.docx”格式）
- 模板复制：先 `Copy-Item 实验报告-范例.docx 实验报告.docx -Force`，保证版式一致再填充内容。
- 内容填充：用 python-docx 读取 `tables[0].rows[3]`，循环写入 8 个单元格，内容只含实验名称/时间/地点/内容/步骤/结果，不要伪代码。时间地点按实际替换。
- C++最简实现要求：先在 `E:\cpp` 新建最小可跑的 `.cpp`（本次示例 ListInsert_Sq.cpp），用 `g++ file.cpp -o file.exe && .\file.exe` 跑通后再把“源文件路径+运行结果”写入报告。
- 编码陷阱：PowerShell 在内联 python 时易因非 ASCII 出现 “byte index is not a char boundary”；改为直接 `python -c` 读写文件或写入脚本后调用，避免长 here-string 透传中文。
- 读取验证：遇到控制台 GBK 编码报错时，用 `python -c "..."` 仅做布尔检查（如包含日期/路径），或在 PowerShell 设置 `$env:PYTHONUTF8=1` 后再打印。
