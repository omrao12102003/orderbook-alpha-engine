#include "backtest/BacktestDriver.hpp"
#include "strategy/ExecutionEngineConsumer.hpp"
#include "Phase5_ExecutionEngine.hpp"

BacktestDriver::BacktestDriver(IEventSource& source)
    : checked_source_(source),
      engine_(checked_source_)
{
}

void BacktestDriver::addConsumer(IEventConsumer* consumer) {
    engine_.addConsumer(consumer);
}

void BacktestDriver::run() {
    engine_.run();
}
