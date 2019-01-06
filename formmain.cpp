#include "formmain.h"
#include "ui_formmain.h"

FormMain::FormMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormMain)
{
    ui->setupUi(this);

    startTimer(1000);

    programsList = new FormProgramsList;
    usersList = new FormUsers;
}

FormMain::~FormMain()
{
    delete programsList;
    delete usersList;
    delete ui;
}

void FormMain::cryptAll()
{
    // .... crypt all programs

    logout();

}

void FormMain::logout()
{
    //... save logs

    emit loggedOut();
    hide();

}



void FormMain::closeEvent(QCloseEvent *event)
{
    event->ignore();
    qDebug() << "Closing main window ...";

    int btn = QMessageBox::question(this, tr("Quit and crypt all"), tr("Are you sure you want to quit and crypt all?"), QMessageBox::Yes, QMessageBox::No);

    if(btn == QMessageBox::Yes){

        ui->labelTimeEllapesed->setText("00:00:00");
        cryptAll();

    }else{

    }
}

void FormMain::showEvent(QShowEvent *event)
{
    startTime = QTime::currentTime();
    ui->labelUsername->setText(property("user").toString());
    event->accept();
}

void FormMain::timerEvent(QTimerEvent *event)
{


    int h = QTime::currentTime().hour() - startTime.hour() ;
    int m = QTime::currentTime().minute() - startTime.minute()  ;
    int s = QTime::currentTime().second() - startTime.second() ;

    QString timeEllapsed = QString::number(h) + ":" + QString::number(m) + ":" + QString::number(s);
    ui->labelTimeEllapesed->setText(timeEllapsed);
}





void FormMain::on_pushButtonProgramsList_clicked()
{

    programsList->show();
}

void FormMain::on_pushButtonUsersList_clicked()
{
    usersList->show();
}
