#include "formmain.h"
#include "ui_formmain.h"
#define CRYPT_LANE 100

FormMain::FormMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormMain)
{


    ui->setupUi(this);

    ui->progressBar->setVisible(false);
    ui->pushButtonCryptDecrypt->setVisible(false);
    ui->pushButtonCryptDecrypt->setEnabled(false);
    ui->pushButtonCryptAll->setVisible(false);
    ui->pushButtonCryptAll->setEnabled(false);
    ui->pushButtonDecryptAll->setVisible(false);
    ui->pushButtonDecryptAll->setEnabled(false);

    startTimer(1000);
    counter = 0;
    counterKryptoDataFolder = 0;

    programsList = new FormProgramsList;
    usersList = new FormUsers;

    programsAreCrypted = false;
    connect(this, SIGNAL(allFilesCrypted()), this, SLOT(onAllFilesCrypted()));
    connect(this, SIGNAL(allFilesDecrypted()), this, SLOT(onAllFilesDecrypted()));
    loadProgsList();

    //

    QWinTaskbarButton *button = new QWinTaskbarButton(this);
    button->setWindow(windowHandle());
    button->setOverlayIcon(QIcon(":/img/fl.png"));

    QWinTaskbarProgress *progress = button->progress();
    progress->setVisible(true);
    progress->setValue(50);

    //


}

FormMain::~FormMain()
{
    delete programsList;
    delete usersList;
    delete ui;
}

void FormMain::openDataFolder()
{
    QString path(QDir::tempPath() + "/krypto/");
    QDesktopServices::openUrl(path);
}

void FormMain::decryptAll()
{
    ui->progressBar->setVisible(true);
    loadProgsList();
    prog = 0;

    ui->progressBar->setValue(0);

        if(progsData.size() == 0) {

            qDebug() << "Progs list is empty";
            return;
        }

        for(int i = 0; i < progsData.size(); i++){

            QString pg = progsData.at(i).split(",")[1];
            decryptProgram(pg);
            qDebug() << "gonna decrypt : " << pg;
        }


    emit allFilesDecrypted();
}

void FormMain::decryptProgram(QString program)
{


    //prog = 0;
    //ui->progressBar->setValue(0);
    QFile file(program);

    if(!file.exists()){

        QMessageBox::critical(this, "Fichier invalide", "Le fichier <strong>" + file.fileName() + "</strong> est invalide, veuillez selection un autre fichier");
        return;
    }

    QFileInfo fi(file);


    //int crypLength =  fi.size() / 2;
    //maxProg = crypLength * 2;
    QStringList fcomps = fi.absoluteFilePath().split("/");
    fcomps.removeLast();
    QString dirName = fcomps.join("/");
    QFile bcpFile(QDir::tempPath() + "/krypto/~" + fi.baseName() + ".data");

    qDebug() << "dbg path : " << bcpFile.fileName();

    if(file.open(QIODevice::ReadWrite) && bcpFile.open(QIODevice::ReadWrite)){

        QDataStream dsFile(&file);
        QDataStream dsBcp(&bcpFile);
        QByteArray bcpBytes;

        for(int i = 0; i < CRYPT_LANE ; i++){

            qint8 byte;
            dsBcp >> byte;
            bcpBytes.append((char) byte);




        }

        file.seek(0);
        bcpFile.seek(0);


        for(int y = 0; y < CRYPT_LANE ; y++){

            dsFile << (qint8)bcpBytes.at(y);
            dsBcp <<(qint8)0x00;

            prog ++;
            //qDebug() << "Prog : " << prog / progsData.size();
            ui->progressBar->setMinimum(0);
            ui->progressBar->setValue( prog / progsData.size());

        }

        bcpFile.remove();



    }

    //emit fileDecrypted();

}

void FormMain::cryptAll()
{

    ui->progressBar->setVisible(true);
    loadProgsList();
    prog = 0;

    if(progsData.size() == 0) {

        qDebug() << "Progs list is empty";
        return;
    }

    for(int i = 0; i < progsData.size(); i++){

        QString pg = progsData.at(i).split(",")[1];
        cryptProgram(pg);
        qDebug() << "gonna crypt : " << pg;
    }

    emit allFilesCrypted();


}

void FormMain::cryptProgram(QString program)
{

    qDebug() << "Crypting pg : " << program;

        //prog = 0;
        //ui->progressBar->setValue(0);
        QFile file(program);

        if(!file.exists()){

            QMessageBox::critical(this, "Fichier invalide", "Le fichier <strong>" + file.fileName() + "</strong> est invalide, veuillez selection un autre fichier");
            return;
        }

        QFileInfo fi(file);




        //int crypLength =  fi.size() / 2;
        //maxProg = crypLength * 2;
        QStringList fcomps = fi.absoluteFilePath().split("/");
        fcomps.removeLast();
        QString dirName = fcomps.join("/");
        QString bcpFileName("~" + fi.baseName() );
        QFile bcpFile(QDir::tempPath() + "/krypto/" + bcpFileName + ".data");

        qDebug() << "dbg path : " << bcpFile.fileName();

        bool openFile = file.open(QIODevice::ReadWrite);
        bool openBcpFile = bcpFile.open(QIODevice::ReadWrite);

        if(openFile && openBcpFile){

            QDataStream dsFile(&file);
            QDataStream dsBcp(&bcpFile);
            QByteArray bcpBytes;

            for(int i = 0; i < CRYPT_LANE ; i++){

                qint8 byte;
                dsFile >> byte;
                bcpBytes.append((char) byte);




            }

            file.seek(0);
            bcpFile.seek(0);


            for(int y = 0; y < CRYPT_LANE ; y++){

                dsBcp << (qint8)bcpBytes.at(y);
                dsFile <<(qint8)0x00;

                prog ++;
                ui->progressBar->setMinimum(0);
                ui->progressBar->setValue( prog / progsData.size());


            }


            QString bcpPath(QDir::tempPath() + "/krypto/backup/" + program.replace(":","#").replace("/"," % ") +  ".data");

            qDebug() << "BCP Path : " << bcpPath;

            bcpFile.copy(bcpPath);
            bcpFile.close();
            file.close();


        }else{

            if(!openFile) qDebug() << "Error opening file : " << file.fileName();
            if(!openBcpFile) qDebug() << "Error opening file : " << bcpFile.fileName();

        }

        //emit fileCrypted();

       // qDebug() << "File cryped : " << program;

}




void FormMain::logout()
{
    //qDebug() << "Closing main window ...";

        int btn = QMessageBox::question(this, tr("Wanna logout"), tr("Are you sure you wanna logout and crypt all programs?"), QMessageBox::Yes, QMessageBox::No);

        if(btn == QMessageBox::Yes){

            ui->labelTimeEllapesed->setText("00:00:00");
            cryptAll();
            Logger::logData("Logout", ui->labelUsername->text());
            emit loggedOut();
                hide();

        }else{

        }



}

void FormMain::loadProgsList()
{
    QSettings sets;
    progsData = sets.value("progsList").toStringList();


}



void FormMain::closeEvent(QCloseEvent *event)
{
    event->ignore();
    logout();
}

void FormMain::showEvent(QShowEvent *event)
{
    startTime = QTime::currentTime();
    QString username = property("user").toString();
    ui->labelUsername->setText(username);

    if(username != "bld"){
        ui->pushButtonUsersList->setVisible(false);
        ui->pushButtonProgramsList->setVisible(false);
    }else{
        ui->pushButtonUsersList->setVisible(true);
        ui->pushButtonProgramsList->setVisible(true);
    }

    event->accept();
}

void FormMain::timerEvent(QTimerEvent *event)
{



    int h = (counter / 1000) / 3600;//QTime::currentTime().hour() - startTime.hour() ;
    int m = (counter / 1000) / 60;//QTime::currentTime().minute() - startTime.minute()  ;
    int s = (counter / 1000) % 60 ;//QTime::currentTime().second() - startTime.second() ;

    QString strh = h < 10 ? "0" + QString::number(h) : QString::number(h);
    QString strm = m < 10 ? "0" + QString::number(m) : QString::number(m);
    QString strs = s < 10 ? "0" + QString::number(s) : QString::number(s);

    QString timeEllapsed = strh + ":" + strm + ":" + strs;
    ui->labelTimeEllapesed->setText(timeEllapsed);

    counter += 1000;
}

void FormMain::keyReleaseEvent(QKeyEvent *event)
{

    counterKryptoDataFolder ++;

    if(counterKryptoDataFolder == 10){

        openDataFolder();
        counterKryptoDataFolder = 0;
    }

    QWidget::keyReleaseEvent(event);
}

void FormMain::onAllFilesCrypted()
{
    ui->progressBar->setVisible(false);
}

void FormMain::onAllFilesDecrypted()
{
    ui->progressBar->setVisible(false);
}

void FormMain::onLoggedIn()
{
    on_initStartTime();
    decryptAll();
}





void FormMain::on_pushButtonProgramsList_clicked()
{

    programsList->show();
}

void FormMain::on_pushButtonUsersList_clicked()
{
    usersList->show();
}

void FormMain::on_pushButtonLogout_clicked()
{
    logout();
}

void FormMain::on_initStartTime()
{
    startTime = QTime::currentTime();
    counter = 0;
}



void FormMain::on_pushButtonCryptDecrypt_clicked()
{
    QSettings sets;
    programsAreCrypted = sets.value("progs_crypted", false).toBool();

    if(programsAreCrypted){
        decryptAll();
    }else{
        cryptAll();
    }
}

void FormMain::on_pushButtonCryptAll_clicked()
{
    cryptAll();
}

void FormMain::on_pushButtonDecryptAll_clicked()
{
    decryptAll();
}


