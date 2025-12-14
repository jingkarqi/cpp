# Repository Guidelines

## Purpose & Scope
- Goal: 快速完成数据结构课程实验报告。按照 `数据结构实验报告选中的伪代码.docx` 里的顺序，每段伪代码实现一个可运行的 C++ 程序，运行取结果，逐条填入 `实验报告.docx`（版式对标 `实验报告-范例.docx`）。运行输出必须来自真实执行，不写伪结果。
- 运行环境：Windows + PowerShell，根目录 `E:\cpp`。

## Project Structure
- 根目录：`实验报告.docx`（当前工作文档）、`实验报告-范例.docx`（版式参考）、`数据结构实验报告选中的伪代码.docx`（任务列表）。
- 代码与工具：`ListInsert_Sq.cpp` 示例，`inject*.py` 用 `python-docx` 写入表格

## End-to-End Workflow
1) **准备版式**：`Copy-Item 实验报告-范例.docx 实验报告.docx -Force`（保持格式干净）。  
2) **读取任务**：打开 `数据结构实验报告选中的伪代码.docx`，按顺序选取下一段伪代码。记录实验名称/步骤/预期输出。  
3) **实现代码**：在根目录创建 `XX.cpp`（按实验序号命名，如 `exp01.cpp`），依据伪代码写最小可运行实现。  
4) **编译运行**：`g++ exp01.cpp -o exp01.exe && .\\exp01.exe`；保存终端输出。  
5) **写入报告**：使用 `python-docx` 脚本（参考 `inject_fill.py` 模式）更新 `实验报告.docx` 的表格：  
   - 实验名称/时间/地点/内容/步骤/结果 各占一行或单元格（依范例表格布局）。  
   - 结果字段附带“源文件：E:\\cpp\\exp01.cpp；运行输出：<粘贴终端结果>”。  
6) **验证**：运行 `python -c "from docx import Document; print(Document(r'E:\\cpp\\实验报告.docx').tables[0].rows[3].cells[0].text)"` 检查写入是否成功。  
7) **重复**：按伪代码顺序继续下一个实验，保持同一份 `实验报告.docx` 追加内容。

## Commands & Tooling
- Python依赖：如需安装先停下并提示用户运行 `python -m pip install python-docx`（遵守“等待确认再继续”策略）。  
- 注入脚本：`python inject_fill.py` / 自写脚本，用 here-string 写入再 `python inject.py`，避免 Bash heredoc。

## Coding Style
- C++：UTF-8，文件 PascalCase 或 `expNN.cpp`，`camelCase` 变量/函数，优先显式头文件。  
- PowerShell：用 `python -c` 或 here-string；不要用 Bash 重定向语法。

## Testing & Validation
- 每个实验至少运行一次可执行文件并记录实际输出。  
- 打开生成的 `实验报告.docx` 目测版式；表格写入后做一次文本读取检查（见第 6 步命令）。  
- 尚无自动化测试；如添加脚本，保持无副作用、可重复。

## Commit & PR
- 建议 Conventional Commits：`feat(exp): add exp01 insertion sort` 或 `chore(doc): update report table`。  
- PR 需说明：完成了哪些伪代码、对应源文件名、运行命令与核心输出；若改版式，附差异截图或描述。  

## Safety Notes
- 操作路径默认 `E:\\cpp`；设置 `$env:PYTHONUTF8=1` 避免 GBK 输出问题。  
- 需要新增依赖时，先停下并把确切安装命令给用户确认（“继续”后再执行）。  
- 保留 `实验报告.docx` 备份；大改前可再复制一份以防回退。
