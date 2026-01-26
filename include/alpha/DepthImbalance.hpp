#pragma once

namespace alpha {

struct DepthImbalance {
    double value;

    constexpr DepthImbalance() noexcept : value(0.0) {}
    constexpr explicit DepthImbalance(double v) noexcept : value(v) {}
};

} // namespace alpha
