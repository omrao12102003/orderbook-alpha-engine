#include "replay/TimeOrderedEventSource.hpp"

TimeOrderedEventSource::TimeOrderedEventSource(IEventSource& source)
    : source_(source),
      last_timestamp_ns_(0),
      first_event_(true)
{
}

bool TimeOrderedEventSource::next(orderbook::OrderEvent& event) {
    if (!source_.next(event)) {
        return false;
    }

    if (first_event_) {
        last_timestamp_ns_ = event.timestamp_ns;
        first_event_ = false;
        return true;
    }

    if (event.timestamp_ns < last_timestamp_ns_) {
        throw std::runtime_error(
            "TimeOrderedEventSource: non-monotonic timestamp detected"
        );
    }

    last_timestamp_ns_ = event.timestamp_ns;
    return true;
}
