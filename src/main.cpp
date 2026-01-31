#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "orderbook/OrderEvent.hpp"
#include "orderbook/OrderBook.hpp"
#include "orderbook/EventType.hpp"
#include "alpha/DepthImbalance.hpp"

using namespace orderbook;

// ------------------------
// Decision rule
// ------------------------
std::string decisionFromAlpha(double alpha) {
    if (alpha >= 0.05) return "BUY";
    if (alpha <= -0.05) return "SELL";
    return "HOLD";
}

int main() {

    // ------------------------
    // Open input CSV
    // ------------------------
    std::ifstream in("data/market_data.csv");
    if (!in.is_open()) {
        std::cerr << "ERROR: Cannot open data/market_data.csv\n";
        return 1;
    }

    // ------------------------
    // Output CSV
    // ------------------------
    std::ofstream csv("build/alpha_stream.csv");
    csv << "timestamp_ns,bid_volume,ask_volume,best_bid,best_ask,"
           "mid_price,obi,depth_imbalance,spread,spread_norm,alpha,decision\n";

    OrderBook book;

    double bid_volume = 0.0;
    double ask_volume = 0.0;

    std::string line;

    // skip header
    std::getline(in, line);

    // ------------------------
    // Replay loop (CSV driven)
    // ------------------------
    while (std::getline(in, line)) {
        std::stringstream ss(line);
        std::string field;

        OrderEvent ev{};

        // timestamp
        std::getline(ss, field, ',');
        ev.timestamp_ns = std::stoll(field);

        // event type
        std::getline(ss, field, ',');
        if (field == "ADD") ev.type = EventType::ADD;
        else if (field == "CANCEL") ev.type = EventType::CANCEL;
        else if (field == "MODIFY") ev.type = EventType::MODIFY;
        else if (field == "TRADE") ev.type = EventType::TRADE;
        else continue; // unknown event

        // is_buy
        std::getline(ss, field, ',');
        ev.is_buy = (field == "1" || field == "true");

        // price
        std::getline(ss, field, ',');
        ev.price = std::stod(field);

        // order_id
        std::getline(ss, field, ',');
        ev.order_id = std::stoll(field);

        // quantity
        std::getline(ss, field, ',');
        ev.quantity = std::stoi(field);

        // ------------------------
        // Apply event
        // ------------------------
        book.onEvent(ev);

        if (ev.type == EventType::ADD || ev.type == EventType::MODIFY) {
            if (ev.is_buy)
                bid_volume += ev.quantity;
            else
                ask_volume += ev.quantity;
        }

        // ------------------------
        // Order Book Imbalance
        // ------------------------
        double obi = 0.0;
        double total = bid_volume + ask_volume;
        if (total > 0.0) {
            obi = (bid_volume - ask_volume) / total;
        }

        // ------------------------
        // Depth imbalance
        // ------------------------
        double depth_value = 0.0;
        if (ask_volume > 0.0) {
            depth_value = bid_volume / ask_volume;
        }
        alpha::DepthImbalance depth(depth_value);

        // ------------------------
        // Best prices
        // ------------------------
        double best_bid = book.bestBid();
        double best_ask = book.bestAsk();

        // ------------------------
        // Spread & mid
        // ------------------------
        double mid = 0.0;
        double spread = 0.0;
        double spread_norm = 0.0;

        if (best_bid > 0.0 && best_ask > best_bid) {
            mid = 0.5 * (best_bid + best_ask);
            spread = best_ask - best_bid;
            spread_norm = spread / mid;
        }

        // ------------------------
        // Composite alpha
        // ------------------------
        double alpha_score = 0.0;
        if (mid > 0.0) {
            alpha_score =
                  0.6 * obi
                + 0.3 * depth.value
                - 0.1 * spread_norm;
        }

        std::string decision = decisionFromAlpha(alpha_score);

        // ------------------------
        // Write CSV
        // ------------------------
        csv << ev.timestamp_ns << ","
            << bid_volume << ","
            << ask_volume << ","
            << best_bid << ","
            << best_ask << ","
            << mid << ","
            << obi << ","
            << depth.value << ","
            << spread << ","
            << spread_norm << ","
            << alpha_score << ","
            << decision << "\n";
    }

    in.close();
    csv.close();

    std::cout << "\n=== Phase 4 completed successfully ===\n";
    return 0;
}

