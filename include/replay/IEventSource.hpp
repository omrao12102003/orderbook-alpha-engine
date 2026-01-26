#pragma once

#include "orderbook/OrderEvent.hpp"

// Interface for any event source (CSV, memory, simulation)
class IEventSource {
public:
    virtual ~IEventSource() = default;

    // Writes the next event into 'event'
    // Returns false when no more events are available
    virtual bool next(orderbook::OrderEvent& event) = 0;
};
