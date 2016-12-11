#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    QTreeWidgetItem *item;
    QFile *file;


    QNetworkAccessManager manager;
    QNetworkReply *currentDownload;
    QNetworkRequest *request;
    QTime downloadTime;

private slots:
    void on_pushButton_clicked();
    void download_finish();

    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void downloadFinished();
    void downloadReadyRead();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
