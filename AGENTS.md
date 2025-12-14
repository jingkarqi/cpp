# Repository Guidelines

## Purpose & Scope
- Goal: 快速完成数据结构课程实验报告。按照 `数据结构实验报告选中的伪代码.docx` 里的顺序，每段伪代码实现一个可运行的 C++ 程序，运行取结果，逐条填入 `实验报告.docx`（版式对标 `实验报告-范例.docx`）。运行输出必须来自真实执行，不写伪结果。
- 运行环境：Windows + PowerShell，根目录 `E:\cpp`。

## Quick Resume（新对话直接接手）
- 固定进入目录并设置编码：`Set-Location E:\cpp; $env:PYTHONUTF8=1`
- 依赖自检：
  - `g++ --version`
  - `python -c "import docx; print(docx.__version__)"`
- 进度判定（避免覆盖/重复注入）：
  - 已有源码：`Get-ChildItem exp??.cpp | Sort-Object Name`
  - 报告已写入次数：`python -c "from docx import Document; t=Document(r'E:\\cpp\\实验报告.docx').tables[0].rows[3].cells[0].text; print(t.count('实验名称：'))"`
- 下一项伪代码读取（表格索引 = 实验号-1）：
  - `python -c "from docx import Document; d=Document(r'E:\\cpp\\数据结构实验报告选中的伪代码.docx'); print(d.tables[1].cell(0,0).text)"`

## Project Structure
- 根目录：`实验报告.docx`（当前工作文档）、`实验报告-范例.docx`（版式参考）、`数据结构实验报告选中的伪代码.docx`（任务列表）。
- 代码与工具：`exp01.cpp`（原 `ListInsert_Sq.cpp` 示例）、`inject*.py` 用 `python-docx` 写入表格

## End-to-End Workflow
1) **准备版式（仅初始化时）**：`Copy-Item 实验报告-范例.docx 实验报告.docx -Force`（保持格式干净；若 `实验报告.docx` 已有进度则禁止覆盖）。  
2) **读取任务**：打开 `数据结构实验报告选中的伪代码.docx`，按顺序选取下一段伪代码。记录实验名称/步骤/预期输出。  
3) **实现代码**：在根目录创建 `XX.cpp`（按实验序号命名，如 `exp01.cpp`），依据伪代码写最小可运行实现。  
4) **编译运行**：`g++ expNN.cpp -o expNN.exe && .\\expNN.exe`；保存终端输出。  
5) **写入报告**：使用 `python-docx` 脚本（参考 `inject_fill.py` 模式）更新 `实验报告.docx` 的表格：  
   - 实验名称/时间/地点/内容/步骤/结果 各占一行或单元格（依范例表格布局）。  
   - 结果字段附带“源文件：E:\\cpp\\exp01.cpp；运行输出：<粘贴终端结果>”。  
6) **验证**：运行 `python -c "from docx import Document; print(Document(r'E:\\cpp\\实验报告.docx').tables[0].rows[3].cells[0].text)"` 检查写入是否成功。  
7) **重复**：按伪代码顺序继续下一个实验，保持同一份 `实验报告.docx` 追加内容。

## Practical Notes（经验总结）
- `数据结构实验报告选中的伪代码.docx` 的“原文伪代码”实际在 **tables** 里（共 10 个表，每表 1 个算法）；段落主要是标题/说明。建议用 `Document(...).tables[k].cell(0,0).text` 精确取伪代码。
- `实验报告-范例.docx` 自带第 1 个实验内容：复制成 `实验报告.docx` 后，把它当作“起始内容”，从第 2 个算法开始 **追加**，不要覆盖已有第 1 个实验。
- `实验报告.docx` 目前只有 1 个表；核心填写区在 `tables[0].rows[3]`。该行在 Word 里是合并单元格，但 `python-docx` 里会表现为多列 `cells` 文本相同；写入时建议更新 `rows[3].cells[0]` 并按需同步到同一行所有 `cells`，避免显示不一致。
- PowerShell 环境避免使用 Bash heredoc（如 `python - <<'PY'`）；优先 `python -c "..."`，或用 here-string：`@'... '@ | python -`。
- 为保证“运行输出来自真实执行”，建议每次运行用 `Tee-Object` 落盘，例如：`.\exp02.exe | Tee-Object -FilePath exp02_output.txt`，注入脚本再读 `exp02_output.txt` 写入报告，减少手工拷贝出错。
- 注入脚本建议“幂等”：写入前先判断 `实验名称：...` 是否已存在，存在则跳过，避免新对话重复运行导致内容翻倍。
- 写入前建议做一次备份：`Copy-Item 实验报告.docx 实验报告.bak.docx -Force`（尤其是准备大段文本/代码时）。

## Algorithm Mapping（表格索引对照）
- `tables[0]` → `exp01`：算法 2.4 `ListInsert_Sq`
- `tables[1]` → `exp02`：算法 2.8 `GetElem_L`
- `tables[2]` → `exp03`：算法 3.1 `InitStack`
- `tables[3]` → `exp04`：算法 3.7 `EnQueue_Sq`
- `tables[4]` → `exp05`：算法 6.1 `PreOrderTraverse`
- `tables[5]` → `exp06`：算法 6.12 `HuffmanCoding`
- `tables[6]` → `exp07`：算法 7.3 `DFSTraverse`
- `tables[7]` → `exp08`：算法 7.15 `ShortestPath_DIJ`
- `tables[8]` → `exp09`：算法 10.6 `Partition`（含快速排序调用）
- `tables[9]` → `exp10`：算法 11.4 `Replace_Selection`

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
