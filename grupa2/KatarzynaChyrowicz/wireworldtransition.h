#ifndef WIREWORLDTRANSITION_H
#define WIREWORLDTRANSITION_H

#include "transition.h"


class WireWorldTransition : public Transition // dziedziczy po transition
{
public:
    WireWorldTransition();
    int getNextState(std::vector<AgentButton*> neighbours, AgentButton *agent); //okresla kolejny stan agenta na podstawie sasiadkow i stanu aktualnego

protected:
    int countNeighboursInState(std::vector<AgentButton*> neighbours, int state); // zlicza liczbe sasiadow agenta o okreslonym stanie, potrzebne, do sprawdzenia przejscia ze stanu 3
};

#endif // WIREWORLDTRANSITION_H
