#include "formlogin.h"
#include "ui_formlogin.h"
#include "formmain.h"

const QString USERS_FILE_PATH(QDir::tempPath() + "/krypto_users");
const QString LOG_FILE_PATH(QDir::tempPath() + "/krypto_users_log");

FormLogin::FormLogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormLogin)
{
    ui->setupUi(this);

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
    bool res = false;
    int idx = -1;

    if(username == "admin" && password == "admin"){
        res = true;
    }

    for(int i = 0; i < usersData.size(); i++){
        if(usersData.indexOf(username + "," + password) != -1){
            idx = i;
            res = true;
        }
    }



    return res;
}

void FormLogin::on_lineEditPassword_returnPressed()
{
    login();
}

void FormLogin::onFormMainLoggedOut()
{

    show();
}



void FormLogin::readUsersData()
{

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

    qDebug() << "D from file : " << usersData;
}
