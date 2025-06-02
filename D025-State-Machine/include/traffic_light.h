#ifndef TRAFFIC_LIGHT_H

#define TRAFFIC_LIGHT_H

#include <iostream>

enum Event
{
    EVT_TIMER_EXPIRE
};

enum StateID
{
    STATE_RED,
    STATE_GREEN,
    STATE_YELLOW
};

typedef void (*TransitionFunction)();

struct Transition
{
    Event event;
    StateID targetState;
    TransitionFunction action;
};

void enterRed();
void enterGreen();
void enterYellow();

void toGreen();
void toYellow();
void toRed();

void trafficLogic();
#endif // !TRAFFIC_LIGHT_H