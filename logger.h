#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QtCore>
#include <QtDebug>
#include <QDateTime>

const QString LOGS_FILE_PATH(QDir::tempPath() + "/krypto_users_log");

class Logger : public QObject
{
    Q_OBJECT
public:
    explicit Logger(QObject *parent = nullptr);

    static void logData(QString logType, QString username);
    static QString loadLogData();


signals:





public slots:
};

#endif // LOGGER_H
