#ifndef FORMPROGRAMSLIST_H
#define FORMPROGRAMSLIST_H

#include <QWidget>
#include "dialogaddprogram.h"
#include <QListWidgetItem>

namespace Ui {
class FormProgramsList;
}

class FormProgramsList : public QWidget
{
    Q_OBJECT

public:
    explicit FormProgramsList(QWidget *parent = 0);
    ~FormProgramsList();

private slots:
    void on_pushButtonAddProgram_clicked();
    void addProgramToList(QString pgName, QString pgPath);

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_pushButtonClearAllPrograms_clicked();

    void on_pushButtonRealoadAllPrograms_clicked();

private:
    QStringList progsData;
    void loadPrograms();
    void addProgram();
    Ui::FormProgramsList *ui;
    QMap<QString, QString> progsDataMap;
};

#endif // FORMPROGRAMSLIST_H
