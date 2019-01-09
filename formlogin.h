#ifndef FORMLOGIN_H
#define FORMLOGIN_H

#include <QWidget>
#include <QtDebug>
#include <QMessageBox>
#include "formmain.h"
#include "logger.h"
#include <QKeyEvent>

namespace Ui {
class FormLogin;
}

class FormLogin : public QWidget
{
    Q_OBJECT

public:
    explicit FormLogin(QWidget *parent = 0);
    ~FormLogin();

private slots:
    void on_pushButtonLogin_clicked();

    void on_lineEditPassword_returnPressed();

private slots:
    void onFormMainLoggedOut();

signals:
    void willLogin();

protected:
    void keyReleaseEvent(QKeyEvent *event);


private:
    int counterResetAdminPassword;
    bool isAdmin;
    void readUsersData();
    QStringList usersData, adminsData;
    FormMain *formMain;
    void login();
    Ui::FormLogin *ui;
    bool userWithPasswordExists(QString username, QString password);
};

#endif // FORMLOGIN_H
