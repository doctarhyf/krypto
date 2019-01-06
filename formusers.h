#ifndef FORMUSERS_H
#define FORMUSERS_H

#include <QWidget>
#include <QtDebug>
#include <QtCore>
#include <QtGui>
#include <QMessageBox>
#include <QListWidgetItem>

namespace Ui {
class FormUsers;
}

class FormUsers : public QWidget
{
    Q_OBJECT

public:
    explicit FormUsers(QWidget *parent = 0);
    ~FormUsers();

private slots:
    void on_pushButtonAddUser_clicked();

    void on_listWidgetUsers_itemClicked(QListWidgetItem *item);

    void on_pushButtonDelUser_clicked();

    void on_lineEditNewPassword_textChanged(const QString &arg1);

private:
    int currentUserRow;
    QStringList usersData;
    void writeUsersDataToFile();
    bool userExists(QString username);
    void addNewUser(QString username, QString password);
    void loadUsers();
    Ui::FormUsers *ui;
};

#endif // FORMUSERS_H
