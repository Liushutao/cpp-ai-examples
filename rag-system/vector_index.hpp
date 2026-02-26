
---

## rag-system 项目

### 文件1: `rag-system/vector_index.hpp`

```cpp
#pragma once
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <cmath>

class VectorIndex {
public:
    struct Document {
        std::string id;
        std::string content;
        std::vector<float> embedding;
    };

    struct SearchResult {
        std::string id;
        std::string content;
        float score;
    };

    explicit VectorIndex(size_t dimension = 384);
    ~VectorIndex();

    void add_document(const Document& doc);
    void add_documents(const std::vector<Document>& docs);
    
    std::vector<SearchResult> search(const std::vector<float>& query_embedding, 
                                      size_t top_k = 5) const;
    size_t size() const;

private:
    size_t dimension_;
    std::vector<Document> documents_;
    
    static float cosine_similarity(const std::vector<float>& a, 
                                    const std::vector<float>& b);
};