#pragma once

#include <cstdint>
#include <type_traits>
#include "orderbook/EventType.hpp"

namespace orderbook {

// One market event (cache-line aligned)
struct alignas(64) OrderEvent {
    EventType type;        // 1 byte
    uint8_t _pad1[7];      // padding

    int64_t order_id;      // 8 bytes
    int64_t timestamp_ns;  // 8 bytes

    double price;          // 8 bytes
    int32_t quantity;      // 4 bytes
    bool is_buy;           // 1 byte
    uint8_t _pad2[3];      // padding
};

// Compile-time guarantees
static_assert(sizeof(OrderEvent) <= 64,
              "OrderEvent must fit in one cache line");
static_assert(std::is_trivially_copyable_v<OrderEvent>,
              "OrderEvent must be trivially copyable");

} // namespace orderbook
