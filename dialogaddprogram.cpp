#include "dialogaddprogram.h"
#include "ui_dialogaddprogram.h"

DialogAddProgram::DialogAddProgram(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddProgram)
{
    ui->setupUi(this);

    path = "";
    programExists = false;
    ui->buttonBox->setEnabled(false);

    startTimer(500);
}

DialogAddProgram::~DialogAddProgram()
{
    delete ui;
}

void DialogAddProgram::timerEvent(QTimerEvent *event)
{
    programExists = QFile(ui->lineEditProgramPath->text()).exists();

    if(programExists){
        ui->buttonBox->setEnabled(true);
        ui->labelProgramNotFound->setVisible(false);

        QFileInfo fi(ui->lineEditProgramPath->text());

        ui->labelProgramName->setText(fi.baseName());

    }else{
        ui->buttonBox->setEnabled(false);
        ui->labelProgramNotFound->setVisible(true);
    }
}

void DialogAddProgram::accept()
{

    QFileInfo fi(QFile(ui->lineEditProgramPath->text()));
    emit programShouldBeAdded(fi.baseName(), ui->lineEditProgramPath->text());
    QDialog::accept();

}





void DialogAddProgram::on_toolButtonLoadPath_clicked()
{
    path = QFileDialog::getOpenFileName(this, tr("Program path"), "C:/tmp/", "*.*");
    programExists = QFile(path).exists();



    if(programExists){

        ui->lineEditProgramPath->setText(path);
    }else{
        QMessageBox::critical(this, tr("Invalid file"), tr("The file selected is invalid, please select another one"));
    }
}
