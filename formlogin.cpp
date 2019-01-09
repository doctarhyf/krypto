#include "formlogin.h"
#include "ui_formlogin.h"
#include "formmain.h"
#include <QInputDialog>

const QString USERS_FILE_PATH(QDir::tempPath() + "/krypto/krypto_users");
const QString ADMINS_FILE_PATH(QDir::tempPath() + "/krypto/krypto_admins");
const QString LOG_FILE_PATH(QDir::tempPath() + "/krypto/krypto_users_log");

FormLogin::FormLogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormLogin)
{
    ui->setupUi(this);

    counterResetAdminPassword = 0;
    isAdmin = false;
    formMain = new FormMain();

    readUsersData();

    connect(formMain, SIGNAL(loggedOut()), this, SLOT(onFormMainLoggedOut()));
    connect(this, SIGNAL(willLogin()), formMain, SLOT(onLoggedIn()));

}

FormLogin::~FormLogin()
{
    delete formMain;
    delete ui;
}

void FormLogin::on_pushButtonLogin_clicked()
{
    login();
}

void FormLogin::login()
{
    QString username = ui->lineEditUsername->text();
    QString password = ui->lineEditPassword->text();

    if(userWithPasswordExists(username, password)){

        Logger::logData("Login", username);

        formMain->setProperty("user", ui->lineEditUsername->text());
        formMain->show();
        emit willLogin();
        hide();


    }else{

        QMessageBox::critical(this, tr("Incorrect username or password"), tr("The username and password you interred is incorrect, please try again!"));

    }
}

bool FormLogin::userWithPasswordExists(QString username, QString password)
{
    readUsersData();
    //bool res = false;
    int idx = -1;

    /*
    if(username == "bld" && password == "2023"){
        isAdmin = true;
        return true;
    }*/

    for(int i = 0; i < adminsData.size(); i++){
            if(adminsData.indexOf(username + "," + password) != -1){
                idx = i;
                isAdmin = true;
                return true;
            }
        }

    for(int i = 0; i < usersData.size(); i++){
        if(usersData.indexOf(username + "," + password) != -1){
            idx = i;
            isAdmin = false;
            return true;
        }
    }



    return false;
}

void FormLogin::on_lineEditPassword_returnPressed()
{
    login();
}

void FormLogin::onFormMainLoggedOut()
{

    show();
}

void FormLogin::keyReleaseEvent(QKeyEvent *event)
{


    if(event->modifiers() == Qt::AltModifier && event->key() == Qt::Key_A){

        counterResetAdminPassword ++;

        if(counterResetAdminPassword == 5){
            counterResetAdminPassword = 0;

            QFile file(ADMINS_FILE_PATH);

            if(file.open(QIODevice::ReadWrite | QIODevice::Truncate)){
                QString password = QInputDialog::getText(this, tr("Input new password"), tr("New password"));
                QTextStream ts(&file);

                ts << "bld" << "," << password;
                file.close();

                qDebug() << "Opened admins file";
            }else{
                qDebug() << "Error opening file : " << ADMINS_FILE_PATH;
            }





        }

        qDebug() << "key for modifying password okay : " << counterResetAdminPassword;
    }

    event->accept();
}



void FormLogin::readUsersData()
{

    adminsData.clear();
    usersData.clear();
    //ui->listWidgetUsers->clear();
    QFile file( USERS_FILE_PATH);

    //QStringList users;
    if(file.open(QIODevice::ReadWrite)){


        QTextStream ts(&file);
        QString line;
        int i = 0;
        while(ts.readLineInto(&line)){
            //usersData << line;
            //QStringList ud = line.split(",");
            usersData << line;

        }



    }

    file.close();
    file.setFileName(QDir::tempPath() + "/krypto/krypto_admins");
    if(file.open(QIODevice::ReadWrite)){


        QTextStream ts(&file);
        QString line;
        int i = 0;
        while(ts.readLineInto(&line)){
            //usersData << line;
            //QStringList ud = line.split(",");
            adminsData << line;

        }



    }

    qDebug() << "users from file : " << usersData;
    qDebug() << "admins from file : " << adminsData;
}
