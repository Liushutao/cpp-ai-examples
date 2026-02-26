# Vector Index for RAG

Lightweight C++ vector similarity search for Retrieval-Augmented Generation.

## Features
- Cosine similarity search
- In-memory index (production: use FAISS/Milvus)
- Zero dependencies

## Build
```bash
mkdir build && cd build
cmake ..
make
./demo