#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "timer.h"
#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QTimeEdit>
#include <QVector>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void addWidget(QString name, QString desc, QTime time, int rButtonState);
    void start_timer();
    QVector<Timer*> timers;


private slots:
    void on_actionNew_triggered();
    void update();
    void delete_timer_clicked();
    void start_timer_clicked();
    void stop_clicked();


private:
    Ui::MainWindow *ui;
    QHash <QPushButton*, Timer*> delBtntoTimerMap;
    QHash <QPushButton*, Timer*> startBtntoTimerMap;
    QHash <QPushButton*, Timer*> stopBtntoTimerMap;
    void redoTimers();
    void timer_complete();
    void delete_timer(Timer *toDel);
    void start_timer(Timer *toStart);
    void repeat_timer();
    QTimer *timerupd;
};
#endif // MAINWINDOW_H
