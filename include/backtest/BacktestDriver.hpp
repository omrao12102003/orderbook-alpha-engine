#pragma once

#include "replay/DeterministicReplayEngine.hpp"
#include "replay/TimeOrderedEventSource.hpp"

// Backtest driver: wires feed -> replay -> consumers
class BacktestDriver {
public:
    explicit BacktestDriver(IEventSource& source);

    // Register a consumer (e.g. OrderBook)
    void addConsumer(IEventConsumer* consumer);

    // Run the backtest
    void run();

private:
    TimeOrderedEventSource checked_source_;
    DeterministicReplayEngine engine_;
};

