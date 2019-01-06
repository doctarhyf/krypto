#ifndef FORMLOGIN_H
#define FORMLOGIN_H

#include <QWidget>
#include <QtDebug>
#include <QMessageBox>

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

private:
    void login();
    Ui::FormLogin *ui;
};

#endif // FORMLOGIN_H
