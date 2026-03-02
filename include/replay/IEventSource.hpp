#pragma once

#include "orderbook/OrderEvent.hpp"

class IEventSource {
public:
    virtual ~IEventSource() = default;

    
    virtual bool next(orderbook::OrderEvent& event) = 0;
};
