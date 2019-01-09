#ifndef FORMMAIN_H
#define FORMMAIN_H

#include <QWidget>
#include <QtDebug>
#include <QtGui>
#include <QtCore>
#include <QMessageBox>
//#include <widgetProgramsList.h>
#include "formusers.h"
#include "formprogramslist.h"
#include "logger.h"

namespace Ui {
class FormMain;
}

class FormMain : public QWidget
{
    Q_OBJECT

public:
    explicit FormMain(QWidget *parent = 0);
    ~FormMain();

private:
    void decryptAll();
    bool programsAreCrypted;
    Ui::FormMain *ui;
    FormProgramsList *programsList;
    FormUsers *usersList;
    void cryptAll();
    void logout();
    void cryptProgram(QString program);
    void decryptProgram(QString program);
    QTime startTime;
    int prog;
    void loadProgsList();
    QStringList progsData;

protected:
    void closeEvent(QCloseEvent *event);
    void showEvent(QShowEvent *event);
    void timerEvent(QTimerEvent *event);

signals:
    void loggedOut();
    void allFilesCrypted();
    void allFilesDecrypted();

private slots:
    void onLoggedIn();
    void on_pushButtonProgramsList_clicked();
    void on_pushButtonUsersList_clicked();
    void on_pushButtonLogout_clicked();
    void on_initStartTime();

    void on_pushButtonCryptDecrypt_clicked();
    void on_pushButtonCryptAll_clicked();
    void on_pushButtonDecryptAll_clicked();
};

#endif // FORMMAIN_H
