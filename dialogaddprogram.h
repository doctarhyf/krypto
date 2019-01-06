#ifndef DIALOGADDPROGRAM_H
#define DIALOGADDPROGRAM_H

#include <QDialog>
#include <QtDebug>
#include <QtGui>
#include <QtCore>
#include <QFileDialog>
#include <QMessageBox>
#include <QTimerEvent>

namespace Ui {
class DialogAddProgram;
}

class DialogAddProgram : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddProgram(QWidget *parent = 0);
    ~DialogAddProgram();

private:
    QString path;
    bool programExists;
    Ui::DialogAddProgram *ui;

protected:
    void timerEvent(QTimerEvent *event);
    void accept();

signals:
    void programShouldBeAdded(QString pgName, QString pgPath);

private slots:
    void on_toolButtonLoadPath_clicked();

};

#endif // DIALOGADDPROGRAM_H
