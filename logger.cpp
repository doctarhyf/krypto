#include "logger.h"

Logger::Logger(QObject *parent) : QObject(parent)
{

}

void Logger::logData(QString logType, QString username)
{
    //QString lt = LOG_TYPE == LOG_TYPE_LOGIN ? "Login : " + "Logout : ";
    QString logData = logType + " : " + QDateTime::currentDateTime().toLocalTime().toString() + " " + username + "\r\n";

    qDebug() << logData;
    qDebug() << LOGS_FILE_PATH;

    QFile file(LOGS_FILE_PATH);

    if(file.open(QIODevice::ReadWrite | QIODevice::Append)){
        QTextStream ts(&file);
        ts << logData;
    }

    file.close();

}

QString Logger::loadLogData()
{
    QString data;
    QFile file(LOGS_FILE_PATH);

        if(file.open(QIODevice::ReadWrite)){
            QTextStream ts(&file);
            QString line;
            while(ts.readLineInto(&line)){
                data.append(line + "<br/>");
            }
        }

        return data;
}
