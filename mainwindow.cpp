#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "newtimer.h"
#include <QPushButton>
#include <QFormLayout>
#include<QTime>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timerupd = new QTimer(this);
    QObject::connect(timerupd, &QTimer::timeout, this, &MainWindow::update);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    NewTimer *wnd = new NewTimer(this);
    wnd->show();
}

void MainWindow::update()
{
    QTime new_t;
    if (timers[0]->timeinNum.second() == 0 && timers[0]->timeinNum.minute() == 0 && timers[0]->timeinNum.hour() == 0)
    {
        timerupd->stop();
        timer_complete();
        return;
    }
    else
        if (timers[0]->timeinNum.second() == 0 && timers[0]->timeinNum.minute() == 0){
            QTime temp (timers[0]->timeinNum.hour() - 1, 59, 59);
            new_t = temp;
        }
    else
            if (timers[0]->timeinNum.second() == 0){
                QTime temp (timers[0]->timeinNum.hour(), timers[0]->timeinNum.minute()-1, 59);
                new_t = temp;
            }
    else
            {
                QTime temp (timers[0]->timeinNum.hour(), timers[0]->timeinNum.minute(), timers[0]->timeinNum.second()-1);
                new_t = temp;
            }



    timers[0]->timeinNum = new_t;
    timers[0]->timeinStr = new_t.toString();
    timers[0]->modify_widget(timers[0]->timerName, timers[0]->timerDesc, timers[0]->timeinStr);
    qWarning()<<timers[0]->timeinStr;
}

void MainWindow::timer_complete()
{
    QMessageBox mb;
    mb.information(this, "Complete", "The timer "+timers[0]->timerName+" has completed it's run!");

    if (timers[0]->rButtonState == 2)
    {
        delete_timer(timers[0]);
    }
    else
        if (timers[0]->rButtonState == 0)
        {
            timers[0]->reset();
        }
    else
            repeat_timer();
}

void MainWindow::redoTimers()
{
    delBtntoTimerMap.clear();
    startBtntoTimerMap.clear();
    stopBtntoTimerMap.clear();
    int k = timers.length();
    QVector<Timer*> temp = timers;
    timers.clear();
    for (int i=0; i<k; i++){
        int m;
    addWidget(temp[i]->timerName, temp[i]->timerDesc, temp[i]->timeinNum, temp[i]->rButtonState);
    }
}

void MainWindow::addWidget(QString name, QString desc, QTime time, int rButtonState)
{
    Timer *add = new Timer(name, desc, time, rButtonState, ui->scrollContent);
    add->modify_widget(add->timerName, add->timerDesc, add->timeinStr);
    timers.push_back(add);

    ui->scrollContent->layout()->addWidget(add);

   QPushButton *delBtn = add->get_deleteButton();
   QPushButton *startBtn = add->get_startButton();
   QPushButton *repeatBtn = add->get_repeatButton();
   QPushButton *stopBtn = add->get_stopButton();
   delBtntoTimerMap.insert(delBtn, add);
   startBtntoTimerMap.insert(startBtn, add);
   stopBtntoTimerMap.insert(stopBtn, add);
   QObject::connect(startBtn, &QPushButton::clicked, this, &MainWindow::start_timer_clicked);
   QObject::connect(delBtn, &QPushButton::clicked, this, &MainWindow::delete_timer_clicked);
   QObject::connect(repeatBtn, &QPushButton::clicked, this, &MainWindow::repeat_timer);
   QObject::connect(stopBtn, &QPushButton::clicked, this, &MainWindow::stop_clicked);
}

void MainWindow::start_timer_clicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    Timer * timer = startBtntoTimerMap.value(button);
    start_timer(timer);
}

void MainWindow::start_timer(Timer *toStart)
{
    if (timerupd->isActive())
    {
        QMessageBox mb;
        mb.warning(this, "Timer", "Another timer is already working!");
        return;
    }

    int i = timers.indexOf(toStart);
    timers.swapItemsAt(0, i);

    timerupd->start(1000);
}

void MainWindow::repeat_timer()
{
    if (timerupd->isActive())
    {
        timerupd->stop();
    }

    timers[0]->reset();
    start_timer(timers[0]);
}

void MainWindow::delete_timer_clicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    Timer* toDel = delBtntoTimerMap.value(button);
    delete_timer(toDel);
}

void MainWindow::delete_timer(Timer *toDel)
{

    int k;
    for (int i=0; i<timers.size(); i++)
        if (toDel == timers[i])
        {
            k = i;
            break;
        }
   timers.removeAt(k);

   qDeleteAll(ui->scrollContent->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));
   delete ui->scrollContent->layout();
   ui->scrollContent->setLayout(new QVBoxLayout);

   redoTimers();
}

void MainWindow::stop_clicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    Timer* timer = delBtntoTimerMap.value(button);

    if (timer != timers[0])
    {
        return;
    }

    if (timerupd->isActive())
    {
        timerupd->stop();
    }
    else
    {
        start_timer(timers[0]);
    }
}


