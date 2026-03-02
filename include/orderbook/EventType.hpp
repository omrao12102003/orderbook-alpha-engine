#pragma once

#include <cstdint>

namespace orderbook {

// Type of market event
enum class EventType : uint8_t {
    ADD = 0,     // New order
    CANCEL = 1,  // Cancel order
    MODIFY = 2,  // Modify order
    TRADE = 3    // Trade execution
};

} // namespace orderbook
