#include "field.h"

Field::Field(int x, int y)
{
    this->x = x;
    this->y = y;
}

#include <QDebug>
void Field::createAgents(Transition *func, int initialState)
{
    qDebug() << "Field::create";
    for(int ix = 0; ix < this->x; ix++)
    {
        std::vector<Agent*> agentVector;
        for(int iy = 0; iy < this->y; iy++)
        {
            Agent *newAgent = new Agent(func, initialState, this);
            agentVector.push_back(newAgent);
        }

        this->agents.push_back(agentVector);
    }
}

void Field::setStates(std::vector<std::vector<int>> states)
{
    for(int ix = 0; ix < x; ix ++)
    {
        for(int iy = 0; iy < y; iy ++)
        {
            int state  = states[ix][iy];
            agents[ix][iy]->setState(state);
        }
    }
}

std::vector<std::vector<int>> Field::getStates()
{
    std::vector<std::vector<int>> states;

    for(int ix = 0; ix < x; ix ++)
    {
        std::vector<int> statesVect;

        for(int iy = 0; iy < y; iy ++)
        {
            int state  = agents[ix][iy]->getState();
            statesVect.push_back(state);
        }

        states.push_back(statesVect);
    }

    return states;
}

void Field::getAgentIndex(Agent *agent, int &x, int &y)
{
    for(int ix = 0; ix < this->x; ix ++)
    {
        for(int iy = 0; iy < this->y; iy ++)
        {
            if (agent == this->agents[ix][iy])
            {
                x = ix;
                y = iy;

                return;
            }
        }
    }
}

std::vector<Agent*> Field::getNeighbours(Agent *agent)
{
    std::vector<Agent*> neighbours;
    int ax = 0;
    int ay = 0;

    this->getAgentIndex(agent, ax, ay);

    for (int ix = ax - 1; ix < ax + 2; ix++)
    {
        if ((ix < 0) || (ix >= x))
        {
            continue;
        }

        for (int iy = ay - 1; iy < ay + 2; iy++)
        {
            if ((iy < 0) || (iy >= y))
            {
                continue;
            }

            if ((ax == ix) && (ay == iy))
            {
                continue;
            }

            neighbours.push_back(this->agents[ix][iy]);
        }
    }

    return neighbours;
}

void Field::step(void)
{
    for(int ix = 0; ix < x; ix ++)
    {
        for(int iy = 0; iy < y; iy ++)
        {
            this->agents[ix][iy]->step1();
        }
    }
    for(int ix = 0; ix < x; ix ++)
    {
        for(int iy = 0; iy < y; iy ++)
        {
            this->agents[ix][iy]->step2();
        }
    }
}


void Field::debugStates(void)
{
    qDebug() << "";
    for(int iy = 0; iy < y; iy ++)
    {
        QString line;
        for(int ix = 0; ix < x; ix ++)
        {
            line += QString::number(this->agents[ix][iy]->getState());
            line += " ";
        }
        qDebug() << line;
    }
}


Field::~Field(void)
{
    qDebug() << "Field::destroy";
    for(int ix = 0; ix < this->x; ix++)
    {
        for(int iy = 0; iy < this->y; iy++)
        {
            delete this->agents[ix][iy];
        }
    }

    this->agents.clear();
}
