#include "traffic_light.h"

void enterRed()
{
    std::cout << "Entering 🔴 RED State \n";
    std::cout << "\n";
}

void enterGreen()
{
    std::cout << "Entering 🟢 GREEN State \n";
    std::cout << "\n";
}

void enterYellow()
{
    std::cout << "Entering 🟡YELLOW State \n";
    std::cout << "\n";
}

void trafficLogic()
{
    std::cout << "🚦 Traffic Light State Machine \n";

    // Start in red state
    StateID currentState = STATE_RED;
    std::cout << "Starting in 🔴 RED \n";
    enterRed();

    // RED to GREEN
    // GREEN to YELLOW
    // YELLOW to RED

    for (int i = 0; i < 3; ++i)
    {
        Event event = EVT_TIMER_EXPIRE;
        std::cout << "Event : EVT_TIMER_EXPIRE received \n";

        switch (currentState)
        {
        case STATE_RED:
            std::cout << "Transitioning to Green \n";
            currentState = STATE_GREEN;
            enterGreen();
            break;

        case STATE_GREEN:
            std::cout << "Transitioning to Yellow \n";
            currentState = STATE_YELLOW;
            enterYellow();
            break;

        case STATE_YELLOW:
            std::cout << "Transitioning to Red \n";
            currentState = STATE_RED;
            enterRed();
            break;

        default:
            break;
        }
    }
}