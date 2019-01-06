#include "formlogin.h"
#include "ui_formlogin.h"
#include "formmain.h"

FormLogin::FormLogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormLogin)
{
    ui->setupUi(this);

    formMain = new FormMain();

    connect(formMain, SIGNAL(loggedOut()), this, SLOT(onFormMainLoggedOut()));
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

        //FormMain main;
        formMain->setProperty("user", ui->lineEditUsername->text());
        formMain->show();
        hide();


    }else{

        QMessageBox::critical(this, tr("Incorrect username or password"), tr("The username and password you interred is incorrect, please try again!"));

    }
}

bool FormLogin::userWithPasswordExists(QString username, QString password)
{
    bool res = false;

    if(username == "admin" && password == "admin"){
        res = true;
    }

    if(username == "doctarhyf" && password == "disck12" ){
        res = true;
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
