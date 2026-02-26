#include "llm_wrapper.hpp"
#include <iostream>

int main() {
    LLMInference::Config cfg;
    cfg.model_path = "models/llama-2-7b.gguf";
    cfg.n_threads = 8;
    
    LLMInference llm(cfg);
    if (!llm.initialize()) {
        std::cerr << "Failed to load model\n";
        return 1;
    }
    
    std::string prompt = "Explain C++ move semantics in simple terms:";
    std::cout << "Prompt: " << prompt << "\n\n";
    
    auto response = llm.generate(prompt, 128);
    std::cout << "Response: " << response << "\n";
    
    return 0;
}