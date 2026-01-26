#include <iostream>
#include <string>

#include "orderbook/OrderBook.hpp"
#include "orderbook/OrderEvent.hpp"
#include "orderbook/EventType.hpp"

// Alpha (Phase 4)
#include "alpha/OrderBookImbalance.hpp"
#include "alpha/OrderBookImbalanceCalculator.hpp"
#include "alpha/DepthImbalance.hpp"
#include "alpha/SpreadDynamics.hpp"

using namespace orderbook;

// ------------------------------------------------------------
// Simple decision rule (Phase 4)
// ------------------------------------------------------------
static std::string decisionFromAlpha(double alpha) {
    if (alpha >= 0.05) return "BUY";
    if (alpha <= -0.05) return "SELL";
    return "HOLD";
}

int main() {
    std::cout << "=== Phase 4: Alpha Engine Demo ===\n";

    // ============================================================
    // ORDER BOOK
    // ============================================================
    OrderBook book;

    // ============================================================
    // EVENTS (DETERMINISTIC MANUAL STREAM)
    // ============================================================
    OrderEvent e1{};
    e1.type = EventType::ADD;
    e1.order_id = 1001;
    e1.timestamp_ns = 1;
    e1.price = 150.25;
    e1.quantity = 100;
    e1.is_buy = true;

    OrderEvent e2{};
    e2.type = EventType::ADD;
    e2.order_id = 2001;
    e2.timestamp_ns = 2;
    e2.price = 150.26;
    e2.quantity = 300;
    e2.is_buy = false;

    OrderEvent e3{};
    e3.type = EventType::MODIFY;
    e3.order_id = 1001;
    e3.timestamp_ns = 3;
    e3.price = 150.25;
    e3.quantity = 40;
    e3.is_buy = true;

    OrderEvent e4{};
    e4.type = EventType::TRADE;
    e4.order_id = 0;
    e4.timestamp_ns = 4;
    e4.price = 0.0;
    e4.quantity = 0;
    e4.is_buy = true;

    OrderEvent e5{};
    e5.type = EventType::CANCEL;
    e5.order_id = 2001;
    e5.timestamp_ns = 5;
    e5.price = 150.26;
    e5.quantity = 0;
    e5.is_buy = false;

    OrderEvent events[] = { e1, e2, e3, e4, e5 };

    double prev_mid = 0.0;

    std::cout << "\nTS | Alpha | Decision\n";

    // ============================================================
    // EVENT LOOP (PHASE 4)
    // ============================================================
    for (const auto& ev : events) {
        book.onEvent(ev);

        double bid = book.bestBid();
        double ask = book.bestAsk();

        if (bid <= 0.0 || ask <= 0.0 || ask <= bid) {
            std::cout << "TS=" << ev.timestamp_ns
                      << " | Book not ready\n";
            continue;
        }

        double mid = 0.5 * (bid + ask);

        // ------------------------
        // Alpha signals
        // ------------------------
        auto obi =
            alpha::OrderBookImbalanceCalculator::compute(book, prev_mid);

        double depth_val = (bid - ask) / (bid + ask);
        alpha::DepthImbalance depth(depth_val);

        alpha::SpreadDynamics spread(ask - bid);
        double spread_norm = spread.spread / mid;

        // ------------------------
        // Composite alpha
        // ------------------------
        double alpha_score =
              0.6 * obi.obi_raw
            + 0.3 * depth.value
            - 0.1 * spread_norm;

        std::string decision = decisionFromAlpha(alpha_score);

        std::cout
            << "TS=" << ev.timestamp_ns
            << " | Alpha=" << alpha_score
            << " | Decision=" << decision
            << "\n";

        prev_mid = mid;
    }

    std::cout << "\n=== Phase 4 completed successfully ===\n";
    return 0;
}
