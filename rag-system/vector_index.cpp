#include "vector_index.hpp"

VectorIndex::VectorIndex(size_t dimension) : dimension_(dimension) {}
VectorIndex::~VectorIndex() = default;

void VectorIndex::add_document(const Document& doc) {
    documents_.push_back(doc);
}

void VectorIndex::add_documents(const std::vector<Document>& docs) {
    documents_.insert(documents_.end(), docs.begin(), docs.end());
}

float VectorIndex::cosine_similarity(const std::vector<float>& a, 
                                      const std::vector<float>& b) {
    float dot = 0.0f, norm_a = 0.0f, norm_b = 0.0f;
    for (size_t i = 0; i < a.size(); ++i) {
        dot += a[i] * b[i];
        norm_a += a[i] * a[i];
        norm_b += b[i] * b[i];
    }
    return dot / (std::sqrt(norm_a) * std::sqrt(norm_b) + 1e-8f);
}

std::vector<VectorIndex::SearchResult> VectorIndex::search(
    const std::vector<float>& query_embedding, size_t top_k) const {
    
    std::vector<SearchResult> results;
    results.reserve(documents_.size());
    
    for (const auto& doc : documents_) {
        float score = cosine_similarity(query_embedding, doc.embedding);
        results.push_back({doc.id, doc.content, score});
    }
    
    std::sort(results.begin(), results.end(), 
              [](const auto& a, const auto& b) { return a.score > b.score; });
    
    if (results.size() > top_k) {
        results.resize(top_k);
    }
    return results;
}

size_t VectorIndex::size() const {
    return documents_.size();
}