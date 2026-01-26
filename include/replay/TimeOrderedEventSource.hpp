#pragma once

#include <cstdint>
#include <stdexcept>

#include "replay/IEventSource.hpp"

// Wraps another event source and enforces monotonic timestamps
class TimeOrderedEventSource : public IEventSource {
public:
    explicit TimeOrderedEventSource(IEventSource& source);

    bool next(orderbook::OrderEvent& event) override;

private:
    IEventSource& source_;
    int64_t last_timestamp_ns_;
    bool first_event_;
};

