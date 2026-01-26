#include "backtest/OrderBookConsumer.hpp"

OrderBookConsumer::OrderBookConsumer(orderbook::OrderBook& book)
    : book_(book)
{
}

void OrderBookConsumer::onEvent(const orderbook::OrderEvent& event) {
    // Forward event to OrderBook unified router
    book_.onEvent(event);
}
