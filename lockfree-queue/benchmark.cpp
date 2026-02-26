#include "lockfree_queue.hpp"
#include <iostream>
#include <chrono>
#include <thread>

void benchmark_spsc() {
    constexpr size_t ITERATIONS = 10'000'000;
    LockFreeQueue<int, 65536> queue;
    
    auto start = std::chrono::high_resolution_clock::now();
    
    std::thread producer([&]() {
        for (int i = 0; i < ITERATIONS; ++i) {
            while (!queue.push(i)) {}
        }
    });
    
    std::thread consumer([&]() {
        int received = 0;
        while (received < ITERATIONS) {
            if (auto val = queue.pop()) {
                ++received;
            }
        }
    });
    
    producer.join();
    consumer.join();
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    double ops_per_sec = static_cast<double>(ITERATIONS) / duration.count() * 1'000'000;
    std::cout << "SPSC: " << duration.count() / 1000.0 << "ms, " 
              << static_cast<size_t>(ops_per_sec) << " ops/sec\n";
}

int main() {
    benchmark_spsc();
    return 0;
}