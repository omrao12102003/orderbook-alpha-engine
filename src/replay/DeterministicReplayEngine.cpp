#include "replay/DeterministicReplayEngine.hpp"

#include <cassert>

// Constructor
DeterministicReplayEngine::DeterministicReplayEngine(IEventSource& source)
    : source_(source)
{
}

// Register a consumer (order is deterministic)
void DeterministicReplayEngine::addConsumer(IEventConsumer* consumer) {
    assert(consumer_count_ < MAX_CONSUMERS);
    consumers_[consumer_count_++] = consumer;
}

// Deterministic replay loop
void DeterministicReplayEngine::run() {
    orderbook::OrderEvent event;

    while (source_.next(event)) {
        for (std::size_t i = 0; i < consumer_count_; ++i) {
            consumers_[i]->onEvent(event);
        }
    }
}
