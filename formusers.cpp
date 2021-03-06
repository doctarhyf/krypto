#include "formusers.h"
#include "ui_formusers.h"
#define USERS_LOG_TAB 1


const QString USERS_FILE_PATH(QDir::tempPath() + "/krypto/krypto_users");

FormUsers::FormUsers(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormUsers)
{
    ui->setupUi(this);

    loadUsers();
    ui->textEditUsersLog->setHtml( Logger::loadLogData());
}

FormUsers::~FormUsers()
{
    delete ui;
}

void FormUsers::on_pushButtonAddUser_clicked()
{
    addNewUser(ui->lineEditNewUsername->text(), ui->lineEditNewPassword->text());
}

bool FormUsers::userExists(QString username)
{
    bool res = false;
    QString filePath = USERS_FILE_PATH;
    QFile file(filePath);

    if(file.open(QIODevice::ReadOnly)){

        QTextStream ts(&file);

        QString user;
        while(ts.readLineInto(&user)){
            QString uname = user.split(",")[0];

            if(uname.toLower() == username.toLower()){
                res = true;
                break;
            }
        }



    }else{
        res = false;
    }

    return res;
}

void FormUsers::addNewUser(QString username, QString password)
{

    if(username == "" || password == ""){
        QMessageBox::critical(this, tr("No empty fields"), tr("Please fill in the name and password"));
        return;
    }

    QString newUser = username + "," + password;

    if(userExists(username)){
        QMessageBox::critical(this, tr("User already exists"), tr("This user already exists"));
        return;
    }

    QFile file( USERS_FILE_PATH);

    QStringList users;
    if(file.open(QIODevice::ReadWrite)){


        QTextStream ts(&file);
        QString line;
        while(ts.readLineInto(&line)){
            users << line;
        }

        if(line.size() > 0){
            users << newUser;
            for(int i = 0; i < users.size(); i ++){
                ts << users.at(i);
            }
        }else{
            ts << newUser << "\r\n";
        }

    }

    QMessageBox::information(this, tr("User added"), tr("New user added successfully"));

    loadUsers();



}

void FormUsers::loadUsers()
{
    currentUserRow = -1;
    usersData.clear();
    ui->listWidgetUsers->clear();
    QFile file( USERS_FILE_PATH);

    QStringList users;
    if(file.open(QIODevice::ReadWrite)){


        QTextStream ts(&file);
        QString line;
        while(ts.readLineInto(&line)){
            usersData << line;
            QStringList ud = line.split(",");
            ui->listWidgetUsers->addItem(ud[0]);
        }



    }

    ui->lineEditNewUsername->clear();
    ui->lineEditNewPassword->clear();
}

void FormUsers::on_listWidgetUsers_itemClicked(QListWidgetItem *item)
{
    ui->pushButtonDelUser->setEnabled(true);
    currentUserRow = ui->listWidgetUsers->currentIndex().row();

    QString user = usersData.at(currentUserRow);
    QStringList ud = user.split(",");

    ui->lineEditNewUsername->setText(ud.at(0));
    ui->lineEditNewPassword->setText(ud.at(1));
}

void FormUsers::on_pushButtonDelUser_clicked()
{
    QFile file(USERS_FILE_PATH);

    if(currentUserRow == -1 ) return;
    qDebug() << usersData;
    usersData.takeAt(currentUserRow);


    writeUsersDataToFile();

    loadUsers();
    qDebug() << usersData;

}

void FormUsers::writeUsersDataToFile()
{
    QFile file(USERS_FILE_PATH);
    if(file.open(QIODevice::ReadWrite | QIODevice::Truncate)){


        QTextStream ts(&file);
        for(int i = 0; i < usersData.size(); i++){
            ts << usersData.at(i) << "\r\n";
        }

    }
}

void FormUsers::on_lineEditNewPassword_textChanged(const QString &arg1)
{

    if(currentUserRow != -1){
        QStringList ud = usersData.at(currentUserRow).split(",");
        ud.replace(1, arg1);

        usersData.replace(currentUserRow, ud.join(","));

        writeUsersDataToFile();
        //loadUsers();
    }
}

void FormUsers::on_tabWidget_currentChanged(int index)
{
    if(index == USERS_LOG_TAB){

        ui->textEditUsersLog->setHtml( Logger::loadLogData());
    }
}

void FormUsers::on_pushButtonClearLog_clicked()
{


    QFile file(LOGS_FILE_PATH);
    //file.remove();
    if(file.open(QIODevice::ReadWrite | QIODevice::Truncate)){

        //file.
        ui->textEditUsersLog->clear();
        QTextStream ts(&file);
        ts << "";

    }
}
