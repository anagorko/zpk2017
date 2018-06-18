#ifndef AGENTBUTTON_H
#define AGENTBUTTON_H

class AgentButton;

#include <QObject>
#include <QPushButton>
#include "fieldlayout.h"
#include "transition.h"

class AgentButton : public QPushButton // dziedziczy po przycisku
{
    Q_OBJECT
public:
    explicit AgentButton(Transition *func, int state, FieldLayout *field, QWidget *parent = Q_NULLPTR);

    int getState(void); // pobiera aktualny stan
    void setState(int state); // nadaje stan
    void setNextState(int state); // nadaje kolejny stan
    void step1(void); // zmiana po pierwszym kroku
    void step2(void); // zmiana po drugim kroku

protected:
    int state; // aktuany stan
    int nextState; // stan po zmianie
    Transition *func = 0; // funkcja przejścia ze stanu do stanu
    FieldLayout *field = 0; // obraz pola
    void formatButton(void); // kształt przycisku
    void setColor(QColor color); // kolor przycisku

private slots:
    void increaseState(void); // zmienia stan po nacisnieciu przycisku na planszy
};

#endif // AGENTBUTTON_H
