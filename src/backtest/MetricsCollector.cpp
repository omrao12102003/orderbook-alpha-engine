#include "backtest/MetricsCollector.hpp"

MetricsCollector::MetricsCollector()
    : event_count_(0),
      last_timestamp_ns_(0)
{
}

void MetricsCollector::onEvent(const orderbook::OrderEvent& event) {
    ++event_count_;
    last_timestamp_ns_ = event.timestamp_ns;
}

std::uint64_t MetricsCollector::eventCount() const {
    return event_count_;
}

std::int64_t MetricsCollector::lastTimestamp() const {
    return last_timestamp_ns_;
}
