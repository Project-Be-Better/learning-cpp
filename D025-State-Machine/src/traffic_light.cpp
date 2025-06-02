#include "traffic_light.h"

// Entry functions
void enterRed() { std::cout << "Entering 🔴 RED\n\n"; }
void enterGreen() { std::cout << "Entering 🟢 GREEN\n\n"; }
void enterYellow() { std::cout << "Entering 🟡 YELLOW\n\n"; }

// Transition functions
void toGreen() { std::cout << "Transition: RED -> GREEN\n"; }
void toYellow() { std::cout << "Transition: GREEN -> YELLOW\n"; }
void toRed() { std::cout << "Transition: YELLOW -> RED\n"; }

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
            toGreen();
            currentState = STATE_GREEN;
            enterGreen();
            break;

        case STATE_GREEN:
            toYellow();
            currentState = STATE_YELLOW;
            enterYellow();
            break;

        case STATE_YELLOW:
            toRed();
            currentState = STATE_RED;
            enterRed();
            break;

        default:
            break;
        }
    }
}