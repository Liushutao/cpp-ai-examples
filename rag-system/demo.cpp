#include "vector_index.hpp"
#include <iostream>

int main() {
    VectorIndex index(4); // 4-dimensional embeddings for demo
    
    // Add documents
    index.add_document({"doc1", "C++ is fast", {0.1f, 0.2f, 0.3f, 0.4f}});
    index.add_document({"doc2", "Python is easy", {0.5f, 0.1f, 0.1f, 0.1f}});
    index.add_document({"doc3", "Rust is safe", {0.2f, 0.3f, 0.1f, 0.5f}});
    
    // Search
    std::vector<float> query = {0.15f, 0.25f, 0.25f, 0.35f};
    auto results = index.search(query, 2);
    
    std::cout << "Top " << results.size() << " results:\n";
    for (const auto& r : results) {
        std::cout << "  [" << r.id << "] " << r.content 
                  << " (score: " << r.score << ")\n";
    }
    
    return 0;
}