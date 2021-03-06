
#include <QApplication>
#include "formlogin.h"
#include <QtDebug>
#include <QtCore>
#include <QFile>
#include <QTextStream>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("K9Soft");
    QCoreApplication::setOrganizationDomain("k9soft.com");
    QCoreApplication::setApplicationName("Krypto");


    QString kryptoRoot(QDir::tempPath() + "/krypto/");
    QString kryptoBcp(QDir::tempPath() + "/krypto/backup/");
    QString pathAdmins(QDir::tempPath() + "/krypto/krypto_admins");

    QDir dir(kryptoRoot);
    if(!dir.exists()){
        dir.mkpath(kryptoRoot);
    }

    dir.setPath(kryptoBcp);
    if(!dir.exists()){
        dir.mkpath(kryptoBcp);
    }

    QFile file(pathAdmins);

    if(!file.exists()){
        if(file.open(QIODevice::ReadWrite)){
            QTextStream ts(&file);
            ts << "bld,2023\r\n";
            file.flush();
            file.close();

            qDebug() << "Admins files written to : " << file.fileName();

        }else{
            qDebug() << "Error writing admins files : " << pathAdmins;
        }
    }

    QTranslator translator;

    if(translator.load("C:/Users/user/Documents/Qt\ Projects/krypto/krypto_fr")){
        a.installTranslator(&translator);
        qDebug() << "krypto_fr loaded!";
    }else{
        qDebug() << "Failed to load trans file ...";
    }



    qDebug() << "Da dir : " << QDir().absoluteFilePath("test.txt");

    FormLogin f;
    f.show();

    return a.exec();
}
