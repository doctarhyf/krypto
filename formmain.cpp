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

    programsAreCrypted = false;
}

FormMain::~FormMain()
{
    delete programsList;
    delete usersList;
    delete ui;
}

void FormMain::decryptAll()
{
    qDebug() << "Decrypting ...";
}

void FormMain::cryptAll()
{
    qDebug() << "Crypting all ...";

}

void FormMain::logout()
{
    //qDebug() << "Closing main window ...";

        int btn = QMessageBox::question(this, tr("Wanna logout"), tr("Are you sure you wanna logout and crypt all programs?"), QMessageBox::Yes, QMessageBox::No);

        if(btn == QMessageBox::Yes){

            ui->labelTimeEllapesed->setText("00:00:00");
            cryptAll();
            Logger::logData("Logout", ui->labelUsername->text());
            emit loggedOut();
                hide();

        }else{

        }



}



void FormMain::closeEvent(QCloseEvent *event)
{
    event->ignore();
    logout();
}

void FormMain::showEvent(QShowEvent *event)
{
    startTime = QTime::currentTime();
    QString username = property("user").toString();
    ui->labelUsername->setText(username);

    if(username != "admin"){
        ui->pushButtonUsersList->setVisible(false);
        ui->pushButtonProgramsList->setVisible(false);
    }else{
        ui->pushButtonUsersList->setVisible(true);
        ui->pushButtonProgramsList->setVisible(true);
    }

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

void FormMain::on_pushButtonLogout_clicked()
{
    logout();
}



void FormMain::on_pushButtonCryptDecrypt_clicked()
{
    QSettings sets;
    programsAreCrypted = sets.value("progs_crypted", false).toBool();

    if(programsAreCrypted){
        decryptAll();
    }else{
        cryptAll();
    }
}
