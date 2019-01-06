#include "formusers.h"
#include "ui_formusers.h"

FormUsers::FormUsers(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormUsers)
{
    ui->setupUi(this);
}

FormUsers::~FormUsers()
{
    delete ui;
}
