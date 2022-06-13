#ifndef DOWNLOADER_H
#define DOWNLOADER_H

// Only for assets/ and librarys/

#include <QObject>
#include <QThread>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QList>
#include <QCryptographicHash>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>

#include "asset_checker.h"

class File;

class Downloader;

class Thread : public QThread
{
    Q_OBJECT
public:
    Thread(Downloader *parent, const File *file);

    const File *file;
    int retryCount = 0; // fails when it is 5
    void run();
signals:
    void threadCompleted();
    void threadFailed();
};

class Downloader : public QObject
{
    Q_OBJECT
public:
    explicit Downloader(QObject *parent = nullptr);

    enum downloaderStatus
    {
        faild,
        progressing,
        completed
    };

    int status = completed;

    Q_PROPERTY(int threads READ getThreads() WRITE setThreads(int threads) NOTIFY threadsChanged());
    int threads = 20;
    int getThreads();
    void setThreads(int threads);

    Q_PROPERTY(int progress READ getProgress() WRITE setProgress(int progress) NOTIFY progressChanged());
    int progress = 0;
    int getProgress();
    void setProgress(int progress);

    QList<File> *downloadList;

    Q_PROPERTY(int total READ getTotal() WRITE setTotal(int total) NOTIFY totalChanged());
    int total = 0;
    int getTotal();
    void setTotal(int total);

    Q_INVOKABLE int startDownload(QList<File> *downloadList);
signals:
    void threadsChanged();
    void progressChanged();
    void totalChanged();
    void stopped();
public slots:
    void onThreadCompleted();
    void onThreadFailed();
};

#endif // DOWNLOADER_H
