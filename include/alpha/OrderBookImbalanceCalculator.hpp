#pragma once

#include "alpha/OrderBookImbalance.hpp"
#include "orderbook/OrderBook.hpp"

namespace alpha {

class OrderBookImbalanceCalculator {
public:
    static OrderBookImbalance compute(
        const orderbook::OrderBook& book,
        double prev_mid
    ) noexcept
    {
        double bid = book.bestBid();
        double ask = book.bestAsk();

        if (bid <= 0.0 || ask <= 0.0 || ask <= bid) {
            return {};
        }

        double mid = 0.5 * (bid + ask);
        double spread = ask - bid;

        double obi = 0.0;
        if (spread > 1e-9) {
            obi = (mid - prev_mid) / spread;
        }

        if (obi > 1.0)  obi = 1.0;
        if (obi < -1.0) obi = -1.0;

        return OrderBookImbalance{obi, 0, 0, 1};
    }
};

} // namespace alpha
