#pragma once

#include <map>
#include <cstdint>
#include "orderbook/PriceLevel.hpp"

namespace orderbook {

enum class Side : uint8_t {
    BID,
    ASK
};

class OrderBookSide {
public:
    explicit OrderBookSide(Side side)
        : side_(side) {}

    // ADD
    void add(double price, int64_t order_id, int32_t qty, int64_t ts) {
        auto it = levels_.find(price);
        if (it == levels_.end()) {
            it = levels_.emplace(price, PriceLevel(price)).first;
        }
        it->second.add(order_id, qty, ts);
    }

    // CANCEL
    bool remove(double price, int64_t order_id) {
        auto it = levels_.find(price);
        if (it == levels_.end()) return false;

        bool ok = it->second.remove(order_id);
        if (ok && it->second.totalQuantity() == 0) {
            levels_.erase(it);
        }
        return ok;
    }

    // MODIFY
    bool modify(double price, int64_t order_id, int32_t reduce_qty) {
        auto it = levels_.find(price);
        if (it == levels_.end()) return false;

        bool ok = it->second.reduce(order_id, reduce_qty);
        if (ok && it->second.totalQuantity() == 0) {
            levels_.erase(it);
        }
        return ok;
    }

    // TRADE — consume FIFO at best price
    bool executeTrade(int32_t trade_qty) {
        if (levels_.empty()) return false;

        auto it = (side_ == Side::BID)
            ? std::prev(levels_.end())
            : levels_.begin();

        auto& level = it->second;

        while (trade_qty > 0 && !level.queue.empty()) {
            auto& order = level.queue.front();

            int32_t consumed = std::min(order.quantity, trade_qty);
            order.quantity -= consumed;
            trade_qty -= consumed;

            if (order.quantity == 0) {
                level.queue.pop_front();
            }
        }

        if (level.totalQuantity() == 0) {
            levels_.erase(it);
        }

        return true;
    }

    double bestPrice() const {
        if (levels_.empty()) return 0.0;
        return (side_ == Side::BID)
            ? levels_.rbegin()->first
            : levels_.begin()->first;
    }

private:
    Side side_;
    std::map<double, PriceLevel> levels_;
};

} // namespace orderbook
