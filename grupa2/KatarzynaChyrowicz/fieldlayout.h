#ifndef FIELDLAYOUT_H
#define FIELDLAYOUT_H

class FieldLayout;

#include <QObject>
#include <QGridLayout>
#include "agentbutton.h"
#include "transition.h"

class FieldLayout : public QGridLayout // dziedziczy po polu do rysowania
{
    Q_OBJECT
public:
    FieldLayout(int x, int y, QWidget *parent, Transition *func, int initialState = 0);
     ~FieldLayout();
    void setStates(std::vector<std::vector<int>> states); // nadaje stany dla calego pola z wektora wektorow
    std::vector<std::vector<int>> getStates(void); // pobiera stany dla calego pola
    std::vector<AgentButton*> getNeighbours(AgentButton *agent); // pobiera sasiadow wybranego agenta
    void step(void); // zmiana stanow po kroku

protected:
    std::vector<std::vector<AgentButton*>> agents; // wektor wektorow stanow agentow
    QWidget *parentWidget;
    int x; // rozmiar x planszy
    int y; // rozmiar y planszy
    void getAgentIndex(AgentButton *agent, int &x, int &y); // pobiera pozycje agenta
    void createAgents(Transition *func, int initialState = 0); // tworzy plansze agentow ze stanem poczatkowym 0

};

#endif // FIELDLAYOUT_H
