#pragma once

#include <cstdint>
#include <deque>

namespace orderbook {

struct Order {
    int64_t order_id;
    int32_t quantity;
    int64_t timestamp;

    Order(int64_t id, int32_t qty, int64_t ts)
        : order_id(id), quantity(qty), timestamp(ts) {}
};

struct alignas(32) PriceLevel {
    double price;
    std::deque<Order> queue;

    explicit PriceLevel(double p) : price(p) {}

    void add(int64_t order_id, int32_t qty, int64_t ts) {
        queue.emplace_back(order_id, qty, ts);
    }

    bool remove(int64_t order_id) {
        for (auto it = queue.begin(); it != queue.end(); ++it) {
            if (it->order_id == order_id) {
                queue.erase(it);
                return true;
            }
        }
        return false;
    }

    bool reduce(int64_t order_id, int32_t qty) {
        for (auto it = queue.begin(); it != queue.end(); ++it) {
            if (it->order_id == order_id) {
                if (it->quantity < qty) return false;
                it->quantity -= qty;
                if (it->quantity == 0) {
                    queue.erase(it);
                }
                return true;
            }
        }
        return false;
    }

    int32_t totalQuantity() const {
        int32_t total = 0;
        for (const auto& o : queue) {
            total += o.quantity;
        }
        return total;
    }

    int queuePosition(int64_t order_id) const {
        int pos = 1;
        for (const auto& o : queue) {
            if (o.order_id == order_id) return pos;
            ++pos;
        }
        return -1;
    }
};

static_assert(alignof(PriceLevel) == 32, "PriceLevel must be 32-byte aligned");

} // namespace orderbook
