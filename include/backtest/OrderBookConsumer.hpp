#pragma once

#include "replay/IEventConsumer.hpp"
#include "orderbook/OrderBook.hpp"

// Adapter: connects replay engine to existing OrderBook
class OrderBookConsumer : public IEventConsumer {
public:
    explicit OrderBookConsumer(orderbook::OrderBook& book);

    void onEvent(const orderbook::OrderEvent& event) override;

private:
    orderbook::OrderBook& book_;
};
