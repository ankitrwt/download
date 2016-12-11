#include "dialog.h"
#include "ui_dialog.h"
#include "downloadmanager.h"

#include <QFileInfo>
#include <QMessageBox>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->treeWidget->setColumnCount(3);
    ui->treeWidget->setHeaderLabels(QStringList() << "URL"<<"Speed"<<"Success"<<"Percent");
    ui->treeWidget->setColumnWidth(0,150);
    ui->treeWidget->setColumnWidth(1,60);
    ui->treeWidget->setColumnWidth(2,60);
    ui->treeWidget->setColumnWidth(3,50);
}

Dialog::~Dialog()
{
    delete ui;
}

//dl.enjoypur.vc/upload_file/367/368/7484/PagalWorld%20-%20Bollywood%20HD%20Video%20Songs%202016/Kahaani%202%20(2016)%20HD%20Video%20Songs/Mehram%20-%20Kahaani%202%20-%20Arijit%20Singh%20%28HD%20720p%29.mp4
void Dialog::on_pushButton_clicked()
{
    QString gotURL = ui->lineEdit->text();
    ui->lineEdit->clear();
    if(gotURL.isEmpty()){
        QMessageBox::information(0,"Information","Enter URL");
        return;
    }

    item = new QTreeWidgetItem(ui->treeWidget);
    item->setText(0,gotURL);

//    DownloadManager manager;
//    manager.append(gotURL);

    QUrl url(gotURL);

    file = new QFile;

    QFileInfo basename(gotURL);

    file->setFileName("/root/Desktop/" + basename.baseName() + "." + basename.suffix());

    if (!file->open(QIODevice::WriteOnly)) {
        qDebug() << "file opening error";
        return;                 // skip this download
    }

    request = new QNetworkRequest;
    request->setUrl(url);
    currentDownload = manager.get(*request);
    connect(currentDownload, SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(downloadProgress(qint64,qint64)));
    connect(currentDownload, SIGNAL(finished()),this,SLOT(downloadFinished()));
    connect(currentDownload, SIGNAL(readyRead()),this,SLOT(downloadReadyRead()));

    // prepare the output
    printf("Downloading %s...\n", url.toEncoded().constData());
    downloadTime.start();


    QObject::connect(&manager, SIGNAL(finished()), this, SLOT(download_finish()));
}

//http://hd.blugaa.com/023819817ec88f0a44feab39e2bffcc0/fqvzv/Koi%20Nahi%20Hai%20Mera-(Mr-Jatt.com).mp3
void Dialog::download_finish()
{
    QMessageBox::information(0,"information","Download Done");
}

void Dialog::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    item->setText(2,QString::number(bytesReceived) + "/" + QString::number(bytesTotal));

    int per = (bytesReceived * 100/bytesTotal);
    item->setText(3,QString::number(per) + "%");

    // calculate the download speed
    double speed = bytesReceived * 1000.0 / downloadTime.elapsed();
    QString unit;
    if (speed < 1024) {
        unit = "bytes/sec";
    } else if (speed < 1024*1024) {
        speed /= 1024;
        unit = "kB/s";
    } else {
        speed /= 1024*1024;
        unit = "MB/s";
    }

    item->setText(1,QString::number(speed) + unit);
//    progressBar.setMessage(QString::fromLatin1("%1 %2")
//                           .arg(speed, 3, 'f', 1).arg(unit));
//    progressBar.update();
}

void Dialog::downloadFinished()
{
//    progressBar.clear();
    file->close();

//    if (currentDownload->error()) {
//        // download failed
//        fprintf(stderr, "Failed: %s\n", qPrintable(currentDownload->errorString()));
//    } else {
//        printf("Succeeded.\n");
//        ++downloadedCount;
//    }

//    currentDownload->deleteLater();
//    startNextDownload();
}

void Dialog::downloadReadyRead()
{
    file->write(currentDownload->readAll());
}
