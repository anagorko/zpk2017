#ifndef TRANSITION_H
#define TRANSITION_H

class Transition;

#include <vector>
#include "agentbutton.h"

class Transition
{
public:
    virtual int getNextState(std::vector<AgentButton*> neighbours, AgentButton* agent) = 0; // klasa abstrakcyjna, okresla kolejny stan agenta na podstawie sasiadkow i stanu aktualnego
};

#endif // TRANSITION_H
