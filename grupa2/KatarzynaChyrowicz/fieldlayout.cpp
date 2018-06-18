#include "fieldlayout.h"
#include "agentbutton.h"


FieldLayout::FieldLayout(int x, int y, QWidget *parent, Transition *func, int state) : QGridLayout(parent)
{  
    this->x = x;
    this->y = y;
    this->setHorizontalSpacing(1);
    this->setVerticalSpacing(1);
    this->parentWidget = parent;
    this->createAgents(func, state);
}

void FieldLayout::createAgents(Transition *func, int initialState) // tworzy plansze agentow
{
    for(int ix = 0; ix < this->x; ix++)
    {
        std::vector<AgentButton*> agentVector; // wektor typu AgentButton
        for(int iy = 0; iy < this->y; iy++)
        {
            AgentButton *newAgent = new AgentButton(func, initialState, this, this->parentWidget); // tworzy nowego agenta stanu initialState
            agentVector.push_back(newAgent); // wklada nowego agenta do wektora agentow
            this->addWidget(newAgent, iy, ix);
        }

        this->agents.push_back(agentVector); // wklada wektor utworzonych agentow do wektora wektorow stanow agentow
    }
}

FieldLayout::~FieldLayout(void) // destruktor
{
    for(int ix = 0; ix < this->x; ix++)
    {
        for(int iy = 0; iy < this->y; iy++)
        {
            delete this->agents[ix][iy]; // czysci plansze z agentow
        }
    }

}

void FieldLayout::setStates(std::vector<std::vector<int>> states) // nadaje stany dla calego pola z wektora wektorow
{
    for(int ix = 0; ix < x; ix ++)
    {
        for(int iy = 0; iy < y; iy ++)
        {
            int state  = states[ix][iy]; // przypisuje podany stan do pola ix iy
            agents[ix][iy]->setState(state); // przypisuje stan dla agenta na polu ix iy
            agents[ix][iy]->setNextState(state); // przypisuje kolejny stan dla agenta na polu ix iy
        }
    }
}

std::vector<std::vector<int>> FieldLayout::getStates() // pobiera stany dla calego pola
{
    std::vector<std::vector<int>> states; // tworzy wektor wektorow stanow

    for(int ix = 0; ix < x; ix ++)
    {
        std::vector<int> statesVect; // tworzy wektor stanow

        for(int iy = 0; iy < y; iy ++)
        {
            int state  = agents[ix][iy]->getState(); // pobbiera stan agenta na polu ix iy
            statesVect.push_back(state); // wklada do wektora stanow stan agenta z pola ix iy
        }

        states.push_back(statesVect); // wklada do wektora wektorow stanow utworzony wektor stanow
    }

    return states; // zwraca stany na calej planszy
}

void FieldLayout::getAgentIndex(AgentButton *agent, int &x, int &y) // pobiera pozycje agenta
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

std::vector<AgentButton*> FieldLayout::getNeighbours(AgentButton *agent) // pobiera sasiadow wybranego agenta
{
    std::vector<AgentButton*> neighbours; // tworzy wektor sasiadow
    int ax = 0;
    int ay = 0;

    this->getAgentIndex(agent, ax, ay); // pobiera pozycje agenta o wspolrzednych ax, ay

    for (int ix = ax - 1; ix < ax + 2; ix++)
    {
        if ((ix < 0) || (ix >= x)) // wyjscie poza plansze
        {
            continue;
        }

        for (int iy = ay - 1; iy < ay + 2; iy++)
        {
            if ((iy < 0) || (iy >= y)) // wyjscie poza plansze
            {
                continue;
            }

            if ((ax == ix) && (ay == iy)) // sprawdzany agent
            {
                continue;
            }

            neighbours.push_back(this->agents[ix][iy]); // wklada do wektora sasiadow stany wybranych agentow (sasiadow) z wektora wektorow stanow agentow
        }
    }

    return neighbours;
}

void FieldLayout::step(void) // zmiana stanow po kroku
{
    for(int ix = 0; ix < x; ix ++)
    {
        for(int iy = 0; iy < y; iy ++)
        {
            this->agents[ix][iy]->step1(); // zmiana po pierwszym kroku dla wszystkich agentow, potrzebne na poczatku symulacji, zeby nextState mialo jakas wartosc
        }
    }
    for(int ix = 0; ix < x; ix ++)
    {
        for(int iy = 0; iy < y; iy ++)
        {
            this->agents[ix][iy]->step2(); // zmiana po drugim kroku
        }
    }
}
