#ifndef FIELD_H
#define FIELD_H

class Field;

#include <vector>
#include "transition.h"
#include "agent.h"
#include <QDebug>

class Field
{
public:
    Field(int x, int y);
    virtual ~Field();

    virtual void createAgents(Transition *func, int initialState = 0);
    virtual void setStates(std::vector<std::vector<int>> states);
    virtual std::vector<std::vector<int>> getStates(void);
    std::vector<Agent*> getNeighbours(Agent *agent);
    void step(void);
    void debugStates(void);

protected:
    int x;
    int y;
    std::vector<std::vector<Agent*>> agents;

protected:
    void getAgentIndex(Agent *agent, int &x, int &y);
};

#endif // FIELD_H
