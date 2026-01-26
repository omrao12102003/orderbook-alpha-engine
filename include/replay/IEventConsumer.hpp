#pragma once

#include "orderbook/OrderEvent.hpp"

// Interface for any component that consumes replayed events
class IEventConsumer {
public:
    virtual ~IEventConsumer() = default;

    // Called once per event in deterministic order
    virtual void onEvent(const orderbook::OrderEvent& event) = 0;
};
