#pragma once

#include <vector>

#include "replay/IEventConsumer.hpp"
#include "orderbook/OrderBook.hpp"
#include "alpha/OrderBookImbalance.hpp"
#include "alpha/OrderBookImbalanceCalculator.hpp"

// ============================================================================
// OrderBookImbalanceConsumer
// ============================================================================
// READ-ONLY consumer
// ============================================================================
class OrderBookImbalanceConsumer final : public IEventConsumer {
public:
    explicit OrderBookImbalanceConsumer(const orderbook::OrderBook& book)
        : book_(book) {}

    void onEvent(const orderbook::OrderEvent& event) override {
        const double bid = book_.bestBid();
        const double ask = book_.bestAsk();

        if (bid <= 0.0 || ask <= 0.0 || ask <= bid) {
            return;
        }

        const double mid = 0.5 * (bid + ask);

        const auto obi =
            alpha::OrderBookImbalanceCalculator::compute(book_, prev_mid_);

        series_.push_back(obi);

        prev_mid_ = mid;
        last_timestamp_ = event.timestamp_ns;
    }

    const std::vector<alpha::OrderBookImbalance>& series() const noexcept {
        return series_;
    }

    size_t count() const noexcept {
        return series_.size();
    }

    double lastValue() const noexcept {
        return series_.empty() ? 0.0 : series_.back().obi_raw;
    }

private:
    const orderbook::OrderBook& book_;
    std::vector<alpha::OrderBookImbalance> series_;
    double prev_mid_ = 0.0;
    uint64_t last_timestamp_ = 0;
};
