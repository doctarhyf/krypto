#include "widgetProgramsList.h"
#include <QApplication>
#include "formlogin.h"
#include <QtDebug>
#include <QtCore>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("K9Soft");
    QCoreApplication::setOrganizationDomain("k9soft.com");
    QCoreApplication::setApplicationName("Krypto");


    QString kryptoRoot(QDir::tempPath() + "/krypto/");
    QString kryptoBcp(QDir::tempPath() + "/krypto/backup/");

    QDir dirRoot(kryptoRoot);
    QDir dirBcp(kryptoBcp);

    if(!dirRoot.exists()){
        dirRoot.mkpath(kryptoRoot);
    }

    if(!dirBcp.exists()){
        dirBcp.mkpath(kryptoBcp);
    }

    FormLogin f;
    f.show();

    return a.exec();
}
