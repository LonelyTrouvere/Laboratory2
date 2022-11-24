#ifndef NEWTIMER_H
#define NEWTIMER_H

#include <QDialog>

namespace Ui {
class NewTimer;
}

class NewTimer : public QDialog
{
    Q_OBJECT

public:
    explicit NewTimer(QWidget *parent = nullptr);
    ~NewTimer();

private slots:
    void on_OKButton_clicked();
    void on_cancleButton_clicked();

private:
    Ui::NewTimer *ui;
};

#endif // NEWTIMER_H
