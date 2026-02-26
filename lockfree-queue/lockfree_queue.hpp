#pragma once
#include <atomic>
#include <memory>
#include <optional>

template<typename T, size_t Capacity>
class LockFreeQueue {
public:
    LockFreeQueue() : head_(0), tail_(0) {
        buffer_ = std::make_unique<T[]>(Capacity);
    }

    bool push(const T& value) {
        size_t current_tail = tail_.load(std::memory_order_relaxed);
        size_t next_tail = (current_tail + 1) % Capacity;
        
        if (next_tail == head_.load(std::memory_order_acquire)) {
            return false;
        }
        
        buffer_[current_tail] = value;
        tail_.store(next_tail, std::memory_order_release);
        return true;
    }

    std::optional<T> pop() {
        size_t current_head = head_.load(std::memory_order_relaxed);
        
        if (current_head == tail_.load(std::memory_order_acquire)) {
            return std::nullopt;
        }
        
        T value = buffer_[current_head];
        head_.store((current_head + 1) % Capacity, std::memory_order_release);
        return value;
    }

    size_t size() const {
        size_t h = head_.load(std::memory_order_acquire);
        size_t t = tail_.load(std::memory_order_acquire);
        return (t >= h) ? (t - h) : (Capacity - h + t);
    }

private:
    std::unique_ptr<T[]> buffer_;
    alignas(64) std::atomic<size_t> head_;
    alignas(64) std::atomic<size_t> tail_;
};