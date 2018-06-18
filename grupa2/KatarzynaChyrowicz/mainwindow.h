#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <fieldlayout.h>
#include "transition.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void load(int table[]); // laduje przykladowa plansze
    void createField(int x, int y, Transition *func); // tworzy plansze o wymiarach x, y, i przejsciami z Transition

private slots:
    void on_actionClose_triggered();

    void on_actionRules_triggered();

    void on_actionAbout_triggered();

    void step(void); // stany po kroku

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_actionEx1_triggered();

    void on_actionEx2_triggered();

    void on_actionEx3_triggered();

    void on_actionEx4_triggered();

    void on_actionEx5_triggered();

    void on_actionNew_triggered();


public slots:
    void updateTimerTimeout(int speed); // ustawia predkosc animacji

private:
    Ui::MainWindow *ui;
    QTimer * fieldTimer;
    FieldLayout * fieldLayout = Q_NULLPTR;
    Transition * func;
};

#endif // MAINWINDOW_H
