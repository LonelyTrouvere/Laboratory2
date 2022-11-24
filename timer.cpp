#include "timer.h"
#include "ui_timer.h"

Timer::Timer(QString name, QString desc, QTime time, int rBtn, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Timer)
{
    ui->setupUi(this);
    this->timerName = name;
    this->timerDesc = desc;
    this->timeinNum = time;
    this->timeinStr = time.toString("hh:mm:ss");
    this->rButtonState = rBtn;
    this->start_time_num = time;
    this->start_time_str = time.toString("hh:mm:ss");
}

void Timer::modify_widget(QString name, QString desc, QString time)
{
    this->ui->nameHere->setText(name);
    this->ui->descrHere->setText(desc);
    this->ui->timeHere->setText(time);
}

void Timer::reset()
{
    this->timeinNum = this->start_time_num;
    this->timeinStr = start_time_str;
    this->modify_widget(this->timerName, this->timerDesc, this->timeinStr);
}

Timer::~Timer()
{
    delete ui;
}

QHBoxLayout *Timer::get_mainLayout()
{
    return ui->mainLayout;
}

QPushButton *Timer::get_deleteButton()
{
    return ui->deleteButton;
}

QPushButton *Timer::get_startButton()
{
    return ui->startButton;
}

QPushButton *Timer::get_repeatButton()
{
    return ui->repeatButton;
}

QPushButton *Timer::get_stopButton()
{
    return ui->stopButton;
}
