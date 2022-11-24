#include "newtimer.h"
#include "mainwindow.h"
#include "ui_newtimer.h"
#include <QTime>
#include <QMessageBox>

NewTimer::NewTimer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewTimer)
{
    ui->setupUi(this);
}

NewTimer::~NewTimer()
{
    delete ui;
}

void NewTimer::on_OKButton_clicked()
{
   QString name = ui->nameTextEdit->toPlainText();
   QString description = ui->descriptionTextEdit->toPlainText();
   QTime time(ui->timeEdit->time().hour(), ui->timeEdit->time().minute(), ui->timeEdit->time().second());

   if (time.hour() == 0 && time.minute() == 0 && time.second() == 0)
   {
       QMessageBox mb;
       mb.warning(this, "Null timer", "The timer is 00:00:00");
       return;
   }

   int rButton;
   if (ui->repeatRB->isChecked())
       rButton = 1;
   else
       if (ui->deleteRB->isChecked())
           rButton = 2;
   else
           rButton = 0;

   MainWindow *wnd = qobject_cast<MainWindow *>(parentWidget());
   this->hide();
   wnd->addWidget(name, description, time, rButton);
}


void NewTimer::on_cancleButton_clicked()
{
    this->hide();
}

