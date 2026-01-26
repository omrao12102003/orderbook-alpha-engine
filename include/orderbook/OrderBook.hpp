#pragma once

#include "orderbook/OrderBookSide.hpp"
#include "orderbook/OrderEvent.hpp"

namespace orderbook {

// ============================================================================
// OrderBook — Phase 2 Final
// Unified routing via OrderEvent
// ============================================================================
class OrderBook {
public:
    OrderBook()
        : bids_(Side::BID),
          asks_(Side::ASK) {}

    // ------------------------------------------------------------------------
    // Unified Event Router (STEP 2.6)
    // ------------------------------------------------------------------------
    void onEvent(const OrderEvent& ev) {
        switch (ev.type) {
            case EventType::ADD:
                add(ev.is_buy,
                    ev.price,
                    ev.order_id,
                    ev.quantity,
                    ev.timestamp_ns);
                break;

            case EventType::CANCEL:
                cancel(ev.is_buy,
                       ev.price,
                       ev.order_id);
                break;

            case EventType::MODIFY:
                modify(ev.is_buy,
                       ev.price,
                       ev.order_id,
                       ev.quantity);
                break;

            case EventType::TRADE:
                trade(ev.is_buy,
                      ev.quantity);
                break;

            default:
                break;
        }
    }

    // ------------------------------------------------------------------------
    // Core Ops
    // ------------------------------------------------------------------------
    void add(bool is_buy,
             double price,
             int64_t order_id,
             int32_t quantity,
             int64_t timestamp_ns) {
        if (is_buy) {
            bids_.add(price, order_id, quantity, timestamp_ns);
        } else {
            asks_.add(price, order_id, quantity, timestamp_ns);
        }
    }

    bool cancel(bool is_buy,
                double price,
                int64_t order_id) {
        return is_buy
            ? bids_.remove(price, order_id)
            : asks_.remove(price, order_id);
    }

    bool modify(bool is_buy,
                double price,
                int64_t order_id,
                int32_t reduce_qty) {
        return is_buy
            ? bids_.modify(price, order_id, reduce_qty)
            : asks_.modify(price, order_id, reduce_qty);
    }

    bool trade(bool is_buy,
               int32_t quantity) {
        return is_buy
            ? asks_.executeTrade(quantity)   // buy hits ask
            : bids_.executeTrade(quantity);  // sell hits bid
    }

    // ------------------------------------------------------------------------
    // Queries
    // ------------------------------------------------------------------------
    double bestBid() const { return bids_.bestPrice(); }
    double bestAsk() const { return asks_.bestPrice(); }

    double spread() const {
        if (bestBid() == 0.0 || bestAsk() == 0.0) return 0.0;
        return bestAsk() - bestBid();
    }

private:
    OrderBookSide bids_;
    OrderBookSide asks_;
};

} // namespace orderbook
