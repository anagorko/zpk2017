#include "wireworldtransition.h"

WireWorldTransition::WireWorldTransition()
{

}

int WireWorldTransition::countNeighboursInState(std::vector<AgentButton*> neighbours, int state) // zlicza liczbe sasiadow agenta o okreslonym stanie, potrzebne, do sprawdzenia przejscia ze stanu 3
{
    int neighboursCount = 0;
    std::vector<AgentButton*>::iterator myAgentVectorIterator; // tworzy iterator, ktory bedzie przechodzil po sasiadach agenta

    for(myAgentVectorIterator = neighbours.begin();
        myAgentVectorIterator != neighbours.end();
        myAgentVectorIterator++)
    {
        if ((*myAgentVectorIterator)->getState() == state)
        {
            neighboursCount++; // jesli stan sasiada rowny stanowi agenta, zwiekszamy licznik
        }
    }

    return neighboursCount;
}

int WireWorldTransition::getNextState(std::vector<AgentButton*> neighbours, AgentButton *agent) //okresla kolejny stan agenta na podstawie sasiadkow i stanu aktualnego
{
    int neighboursCount = 0;

    switch(agent->getState())
    {
        case 0:
            return 0;

        case 1:
            return 2;

        case 2:
            return 3; // zmiany dla stanow 0, 1, 2

        case 3:
            neighboursCount = this->countNeighboursInState(neighbours, 1); // dla stanu 3 sprawdza, ilu sasiadow o stanie 1

            if ((neighboursCount == 1) || (neighboursCount == 2))
            {
                return 1; // jesli 1 lub 2 sasiadow o stanie 1, zmiana na stan 1
            }
            else
            {
                return 3; // jesli inna liczba sasiadow o stnie 1, pozostaje w stanie 3
            }

        default:
            return 0;
    }
}
