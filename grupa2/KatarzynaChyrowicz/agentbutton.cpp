#include "agentbutton.h"

AgentButton::AgentButton(Transition *func, int state, FieldLayout *field, QWidget *parent) : QPushButton(parent)
{
    this->field = field;
    this->func = func;
    this->setNextState(state);
    this->setState(state);
    this->formatButton();
}

void AgentButton::formatButton(void) // kształt przycisku
{
    this->setFlat(true);
    this->setAutoFillBackground(true);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    connect(this, SIGNAL(clicked(bool)), this, SLOT(increaseState())); // nacisniecie przycisku zmienia stan
}

void AgentButton::setColor(QColor color) // kolor przycisku
{
    this->setPalette(QPalette(color));
}

void AgentButton::setState(int state) // nadaje stan
{
    this->state = state;

    switch(state)
    {
        case 0:
            this->setColor(QColor(0, 0, 0)); // jesli 0, to czarny
            break;

        case 1:
            this->setColor(QColor(255, 0, 0)); // jesli 1, to czerwony
            break;

        case 2:
            this->setColor(QColor(0, 255, 0)); // jesli 2, to zielony
            break;

        case 3:
            this->setColor(QColor(0, 0, 255)); // jesli 3, to niebieski
            break;

        default:
            this->setColor(QColor(255, 255, 255)); // default bialy
            break;
    }
}

void AgentButton::setNextState(int state) // nadaje kolejny stan
{
    this->nextState = state;
}

void AgentButton::step1(void) // zmiana po pierwszym kroku, potrzebne na poczatku symulacji, zeby nextState mialo jakas wartosc
{
    this->setState(this->nextState); // przypisuje do stanu akutalnego stan po zmianie
}

void AgentButton::step2(void) // zmiana po drugim kroku
{
    this->setNextState(this->func->getNextState(this->field->getNeighbours(this), this)); // ustala stan po zmianie, w zaleznosci od sasiadow i stanu obecnego (funkcji przejscia)
}

int AgentButton::getState(void) //pobiera aktualny stan
{
    return this->state;
}


void AgentButton::increaseState() // zmienia stan po nacisnieciu przycisku na planszy
{
    int currentState = this->getState(); // przypisuje do nowej zmiennej aktualny stan agenta

    currentState++; // zwieksza wartosc stanu

    if (currentState > 3) // jesli stan po zmianie wiekszy niz 3, powrot do 0, bo nie ma wiecej stanow
    {
        currentState = 0;
    }

    this->setState(currentState);
    this->setNextState(currentState);
}
