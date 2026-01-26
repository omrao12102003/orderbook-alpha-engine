#pragma once

#include <ostream>

namespace alpha {

struct OrderBookImbalance {
    double obi_raw;
    int bid_volume;
    int ask_volume;
    int levels_used;

    constexpr OrderBookImbalance() noexcept
        : obi_raw(0.0), bid_volume(0), ask_volume(0), levels_used(0) {}

    constexpr OrderBookImbalance(
        double obi,
        int bid_vol,
        int ask_vol,
        int levels
    ) noexcept
        : obi_raw(obi),
          bid_volume(bid_vol),
          ask_volume(ask_vol),
          levels_used(levels) {}

    friend std::ostream& operator<<(std::ostream& os,
                                    const OrderBookImbalance& obi) {
        os << "OBI{raw=" << obi.obi_raw << "}";
        return os;
    }
};

} // namespace alpha

