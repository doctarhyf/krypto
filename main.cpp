#include "widgetProgramsList.h"
#include <QApplication>
#include "formlogin.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("K9Soft");
    QCoreApplication::setOrganizationDomain("k9soft.com");
    QCoreApplication::setApplicationName("Krypto");

    FormLogin f;
    f.show();

    return a.exec();
}
