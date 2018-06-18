#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "rulesdialog.h"
#include "agentbutton.h"
#include "fieldlayout.h"
#include "wireworldtransition.h"
#include "example1.h"
#include "example2.h"
#include "example3.h"
#include "example4.h"
#include "example5.h"

void MainWindow::updateTimerTimeout(int speed) // ustawia predkosc animacji
{
    this->fieldTimer->setInterval(5000 * (100 - speed) / 100);
}

void MainWindow::step(void) // stany po kroku
{
    this->fieldLayout->step(); // zmiana stanow po kroku z fieldLayout
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->func = new WireWorldTransition(); // przypisanie do func zasad Wire World
    this->createField(5, 5, this->func); // utworzenie planszy domyślnej po uruchomieniu

    this->fieldTimer = new QTimer(this);
    connect(this->fieldTimer, SIGNAL(timeout()), this, SLOT(step()));
    connect(ui->spinBox, SIGNAL(valueChanged(int)), this, SLOT(updateTimerTimeout(int)));
    this->updateTimerTimeout(ui->horizontalSlider->value());
}


void MainWindow::createField(int x, int y, Transition *func) // tworzy plansze o wymiarach x, y, i przejsciami z Transition
{
    if (this->fieldLayout != Q_NULLPTR)
    {
        ui->gridLayout->removeItem(this->fieldLayout);
        delete this->fieldLayout;
    }

    this->fieldLayout = new FieldLayout(x, y, this, func);
    ui->horizontalLayout_3->insertLayout(-1, this->fieldLayout);
}


void MainWindow::load(int table[]) // laduje przykladowa plansze
{
    int pos = 0;
    int x = table[pos++];
    int y = table[pos++];
    std::vector<std::vector<int>> example;
    for (int ix = 0; ix < x; ix++)
    {
        std::vector<int> row;
        for (int iy = 0; iy < y; iy++)
        {
            row.push_back(table[pos++]);
        }
        example.push_back(row);
    }

    this->createField(x, y, this->func);
    this->fieldLayout->setStates(example);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionClose_triggered()
{
  this->close();
}

void MainWindow::on_actionRules_triggered()
{
    RulesDialog dialog;
    dialog.show();
    dialog.exec();
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog dialog;
    dialog.show();
    dialog.exec();

}

void MainWindow::on_pushButton_2_clicked()
{
    this->fieldTimer->start();
}

void MainWindow::on_pushButton_clicked()
{
    this->fieldTimer->stop();
}

void MainWindow::on_pushButton_3_clicked()
{
    this->createField(ui->X_size->value(), ui->Y_size->value(), this->func);
}

void MainWindow::on_pushButton_4_clicked()
{
    this->step();
}

void MainWindow::on_actionEx1_triggered() // przypisanie do przycisku kolejnych przykladow
{
    this->load((int*)example1);
}

void MainWindow::on_actionEx2_triggered()
{
    this->load((int*)example2);
}

void MainWindow::on_actionEx3_triggered()
{
    this->load((int*)example3);
}


void MainWindow::on_actionEx4_triggered()
{
    this->load((int*)example4);
}

void MainWindow::on_actionEx5_triggered()
{
    this->load((int*)example5);
}

void MainWindow::on_actionNew_triggered() // utworzenie planszy o podanych rozmiarach po nacisnieciu przycisku new
{
    this->createField(ui->X_size->value(), ui->Y_size->value(), this->func);
}

