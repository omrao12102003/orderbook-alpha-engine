#pragma once

#include <cstdint>

#include "replay/IEventConsumer.hpp"

// Simple metrics collector for backtesting
class MetricsCollector : public IEventConsumer {
public:
    MetricsCollector();

    void onEvent(const orderbook::OrderEvent& event) override;

    std::uint64_t eventCount() const;
    std::int64_t lastTimestamp() const;

private:
    std::uint64_t event_count_;
    std::int64_t last_timestamp_ns_;
};

