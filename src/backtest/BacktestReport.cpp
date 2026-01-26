#include "backtest/BacktestReport.hpp"

void BacktestReport::print(
    const MetricsCollector& metrics,
    const orderbook::OrderBook& book
) {
    std::cout << "\n===== BACKTEST REPORT =====\n";
    std::cout << "Total events   : " << metrics.eventCount() << "\n";
    std::cout << "Last timestamp : " << metrics.lastTimestamp() << " ns\n";
    std::cout << "Best Bid       : " << book.bestBid() << "\n";
    std::cout << "Best Ask       : " << book.bestAsk() << "\n";
    std::cout << "Spread         : " << book.spread() << "\n";
    std::cout << "===========================\n";
}
