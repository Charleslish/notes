# notes

个人的计算机科学学习知识库（personal CS knowledge base）。课程材料、自己的理解和练习分开保存；课程提供的文件不覆盖原件。

## Python

CS-py 是 Python 相关课程的学习知识库。
对于配置 .venv 环境，推荐使用 `python -m venv .venv` 命令。
使用 `source .venv/bin/activate` 激活环境。
为了使用jupyter notebook，需要安装 `ipykernel` 包：`pip install ipykernel`。
- `CS-py/CS101/`、`CS-py/CS107/`、`CS-py/CS173/`、`CS-py/CS233/`：对应课程笔记
- `CS-py/CS357/`
  - `Course/`：课程提供的原始材料（例如 PrairieLearn/Jupyter notebooks）
  - `Notes/`：自己的概念笔记与推导
  - `Practice/`：自己的练习与实验
- `CS-py/Python/`：通用 Python 笔记
- `CS-py/NumPy/`、`CS-py/Pandas/`、`CS-py/Machine-Learning/`：专题笔记

## C++ 与 C++-heavy CS

- `C++/CS128/`、`C++/CS225/`：对应课程笔记
- `C++/Algorithms/`、`C++/STL/`：语言与算法专题

## 约定

- ignore规则：
  - 所有目录下的 `__pycache__/` 文件夹
  - 所有目录下的 `.DS_Store` 文件
  - 所有目录下的 `build/` 文件夹和 `bin/` 文件夹
- 空目录用 `.gitkeep` 保留，以便整个框架同步到 GitHub。
