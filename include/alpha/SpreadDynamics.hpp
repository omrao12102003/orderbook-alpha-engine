#pragma once

namespace alpha {

struct SpreadDynamics {
    double spread;

    constexpr SpreadDynamics() noexcept : spread(0.0) {}
    constexpr explicit SpreadDynamics(double s) noexcept : spread(s) {}
};

} // namespace alpha
