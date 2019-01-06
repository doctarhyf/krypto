#include "formlogin.h"
#include "ui_formlogin.h"
#include "formmain.h"

FormLogin::FormLogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormLogin)
{
    ui->setupUi(this);
}

FormLogin::~FormLogin()
{
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

        FormMain main;
        main.show();


    }else{

        QMessageBox::critical(this, tr("Incorrect username or password"), tr("The username and password you interred is incorrect, please try again!"));

    }
}
