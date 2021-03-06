#ifndef RULESDIALOG_H
#define RULESDIALOG_H

#include <QDialog>

namespace Ui {
class RulesDialog;
}

class RulesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RulesDialog(QWidget *parent = 0);
    ~RulesDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::RulesDialog *ui;
};

#endif // RULESDIALOG_H
