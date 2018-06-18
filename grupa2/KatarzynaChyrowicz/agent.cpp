#include "agent.h"


Agent::Agent(Transition *func, int state, Field *field)
{
    this->field = field;
    this->func = func;
    this->setNextState(state);
    this->setState(state);
}

#include <QDebug>
void Agent::setState(int state)
{
    //qDebug() << "Agent::setState " << QString::number(state);
    this->state = state;
}

void Agent::setNextState(int state)
{
    //qDebug() << "Agent::setNextState " << QString::number(state);
    this->nextState = state;
}

void Agent::step1(void)
{
    this->setState(this->nextState);
}

void Agent::step2(void)
{
    this->setNextState(this->func->getNextState(this->field->getNeighbours(this), this));
}

int Agent::getState(void)
{
    return this->state;
}
