#pragma once

#include <cstddef>

#include "replay/IEventConsumer.hpp"
#include "replay/IEventSource.hpp"

// Deterministic, single-threaded replay engine
class DeterministicReplayEngine {
public:
    explicit DeterministicReplayEngine(IEventSource& source);

    // Register a consumer (order matters, max is fixed)
    void addConsumer(IEventConsumer* consumer);

    // Start replay (implementation comes later)
    void run();

private:
    static constexpr std::size_t MAX_CONSUMERS = 8;

    IEventSource& source_;
    IEventConsumer* consumers_[MAX_CONSUMERS];
    std::size_t consumer_count_ = 0;
};
