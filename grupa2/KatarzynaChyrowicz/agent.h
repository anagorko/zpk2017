#ifndef AGENT_H
#define AGENT_H

class Agent;

#include "field.h"
#include "transition.h"


class Agent
{
public:
    Agent(Transition *func, int state, Field *field);
    virtual int getState(void);
    virtual void setState(int state);
    virtual void setNextState(int state);
    void step1(void);
    void step2(void);

protected:
    int state;
    int nextState;
    Transition *func = 0;
    Field *field = 0;
};

#endif // AGENT_H
