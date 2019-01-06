#include "formprogramslist.h"
#include "ui_formprogramslist.h"

FormProgramsList::FormProgramsList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormProgramsList)
{
    ui->setupUi(this);

    loadPrograms();
    ui->pushButtonRunProgram->setVisible(false);

}

void FormProgramsList::loadPrograms()
{
    QSettings sets;
    progsData = sets.value("progsList").toStringList();

    ui->listWidget->clear();

    for(int i = 0; i < progsData.size(); i++){
        QString pg = progsData.at(i);
        QStringList pgData = pg.split(",");

        progsDataMap.insert(pgData[1], pgData[0]);

        ui->listWidget->addItem(pgData[0]);


    }

    qDebug() << progsDataMap[0];

}

FormProgramsList::~FormProgramsList()
{
    delete ui;
}

void FormProgramsList::on_pushButtonAddProgram_clicked()
{
    addProgram();
}

void FormProgramsList::addProgramToList(QString pgName, QString pgPath)
{
    QSettings sets;
    QString progData = pgName + "," + pgPath;

    if(sets.value("progsList").isNull()){
        QStringList progs;
        progs << progData;
        sets.setValue("progsList", QVariant(progs));
    }else{
        QStringList progs = sets.value("progsList").toStringList();
        bool exists = false;
        for(int i = 0; i < progs.size(); i++){
            QString prog = progs.at(i);

            if(prog.indexOf(pgPath) != -1){
                exists = true;
            }
        }

        if(exists == false){
            progs << progData;
            sets.setValue("progsList", QVariant(progs));
        }else{
            qDebug() << "Program [" << pgPath << "] already exists";

            QMessageBox::critical(this, tr("Program already exists"), tr("Sorry this program already exists"));
        }
    }


    loadPrograms();


    //sets.clear();


    //qDebug() << "progList : ";
    //qDebug() << sets.value("progsList");

}



void FormProgramsList::addProgram()
{

    DialogAddProgram dg;

    connect(&dg, SIGNAL(programShouldBeAdded(QString,QString)), this, SLOT(addProgramToList(QString, QString)));

    if(dg.exec() == QDialog::Accepted){
        qDebug() << "Accept";
    }else{
        qDebug() << "Reject";
    }

    disconnect(&dg, SIGNAL(programShouldBeAdded(QString,QString)), this, SLOT(addProgramToList(QString, QString)));
}

void FormProgramsList::on_listWidget_itemClicked(QListWidgetItem *item)
{

    int row = ui->listWidget->currentIndex().row();
    QStringList  pd = progsData.at(row).split(",");

    ui->pushButtonRunProgram->setEnabled(true);

    ui->labelProgName->setText(pd.at(0));
    ui->labelProgPath->setText(pd.at(1));

    currentProgPath = pd.at(1);


    qDebug() << pd;

 }

void FormProgramsList::on_pushButtonClearAllPrograms_clicked()
{

    int res = QMessageBox::question(this, tr("Delete all program?"), tr("Are you sure you wanna remove all programs?"), QMessageBox::Yes, QMessageBox::No);

    if(res != QMessageBox::Yes){
        return;
    }

    QSettings set;
    set.remove("progsList");
    loadPrograms();
    ui->labelProgName->setText("...");
    ui->labelProgPath->setText("...");
}

void FormProgramsList::on_pushButtonRealoadAllPrograms_clicked()
{
    loadPrograms();
}

void FormProgramsList::on_pushButtonRunProgram_clicked()
{

}

void FormProgramsList::on_pushButtonDeleteProgram_clicked()
{

    int res = QMessageBox::question(this, tr("Delete the program?"), tr("Are you sure you wanna delete this program?"), QMessageBox::Yes, QMessageBox::No);

    if(res != QMessageBox::Yes){
        return;
    }


    qDebug() << "Deleting : " << currentProgPath;

    QSettings sets;
    QStringList progs = sets.value("progsList").toStringList();

    for(int i = 0 ; i < progs.size(); i++){
        QString prog = progs.at(i);
        if(prog.indexOf(currentProgPath) != -1){
            progs.removeAt(i);
            break;
        }
    }

    sets.setValue("progsList", progs);
    loadPrograms();
}
