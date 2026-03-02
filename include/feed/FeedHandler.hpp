#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>

#include "orderbook/OrderEvent.hpp"

namespace feed {

class FeedHandler {
public:
    static std::vector<orderbook::OrderEvent>
    load_csv(const std::string& filepath) {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + filepath);
        }

        std::vector<orderbook::OrderEvent> events;
        std::string line;

        // Skip header
        std::getline(file, line);

        while (std::getline(file, line)) {
            if (line.empty()) continue;
            events.push_back(parse_line(line));
        }

        return events;
    }

private:
    static orderbook::OrderEvent parse_line(const std::string& line) {
        std::stringstream ss(line);
        std::string token;

        // timestamp
        std::getline(ss, token, ',');
        int64_t timestamp = std::stoll(token);

        // event_type
        std::getline(ss, token, ',');
        orderbook::EventType type = parse_event_type(token);

        // order_id
        std::getline(ss, token, ',');
        int64_t order_id = std::stoll(token);

        // price
        std::getline(ss, token, ',');
        double price = std::stod(token);

        // quantity
        std::getline(ss, token, ',');
        int32_t quantity = std::stoi(token);

        // is_buy
        std::getline(ss, token, ',');
        bool is_buy = (token == "true");

        return orderbook::OrderEvent{
            type,
            {0},
            order_id,
            timestamp,
            price,
            quantity,
            is_buy,
            {0}
        };
    }

    static orderbook::EventType parse_event_type(const std::string& s) {
        if (s == "ADD")    return orderbook::EventType::ADD;
        if (s == "CANCEL") return orderbook::EventType::CANCEL;
        if (s == "MODIFY") return orderbook::EventType::MODIFY;
        if (s == "TRADE")  return orderbook::EventType::TRADE;
        throw std::runtime_error("Unknown event type: " + s);
    }
};

} // namespace feed
