
---

## 更新根目录 README

把 `README.md` 改成：

```markdown
# C++ AI Examples

High-performance C++ systems for AI applications.

## Projects

| Project | Description | Performance |
|---------|-------------|-------------|
| `lockfree-queue/` | SPSC lock-free queue | 100M+ ops/sec |
| `llm-inference/` | LLM inference wrapper | <100ms latency |
| `rag-system/` | Vector similarity search | Cosine similarity |

## Quick Start

Each project is standalone:

```bash
cd <project-name>
mkdir build && cd build
cmake ..
make
./demo  # or ./benchmark
