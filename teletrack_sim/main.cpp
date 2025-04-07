#include "gnss_simulator.h"
#include "engine_simulator.h"
#include "logger.h"
#include "aggregator.h"

int main()
{
    GNSSSimulator gnss_simulator;
    EngineSimulator engine_simulator;
    Logger logger;
    Aggregator aggregator;

    gnss_simulator.sayHello();
    engine_simulator.sayHello();
    logger.sayHello();
    aggregator.sayHello();

    return 0;
};