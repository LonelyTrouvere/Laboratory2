#ifndef TIMER_H
#define TIMER_H

#include <QPushButton>
#include <QWidget>
#include <QHBoxLayout>
#include <QTime>

namespace Ui {
class Timer;
}

class Timer : public QWidget
{
    Q_OBJECT

public:
    explicit Timer(QString name, QString desc, QTime time, int rBtn, QWidget *parent = nullptr);
    ~Timer();
    int rButtonState;
    QTime timeinNum;
    QString timeinStr;
    QString timerName;
    QString timerDesc;

    QHBoxLayout *get_mainLayout();
    void modify_widget(QString name, QString desc, QString time);
    void reset();
    QPushButton * get_deleteButton();
    QPushButton *get_startButton();
    QPushButton *get_repeatButton();
    QPushButton *get_stopButton();

private:
    Ui::Timer *ui;
    QTime start_time_num;
    QString start_time_str;
};

#endif // TIMER_H
