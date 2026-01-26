#pragma once

#include <iostream>

#include "backtest/MetricsCollector.hpp"
#include "orderbook/OrderBook.hpp"

// Simple deterministic backtest report
class BacktestReport {
public:
    static void print(
        const MetricsCollector& metrics,
        const orderbook::OrderBook& book
    );
};
