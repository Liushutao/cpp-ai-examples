#pragma once
#include <string>
#include <vector>
#include <memory>
#include <functional>

class LLMInference {
public:
    struct Config {
        std::string model_path;
        int n_ctx = 2048;
        int n_threads = 4;
        float temperature = 0.7f;
    };

    explicit LLMInference(const Config& config);
    ~LLMInference();
    
    bool initialize(std::string* error_msg = nullptr);
    std::string generate(const std::string& prompt, int max_tokens = 256);
    void generate_stream(const std::string& prompt, 
                        std::function<void(const std::string&)> callback,
                        int max_tokens = 256);
    bool is_ready() const;

private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
};