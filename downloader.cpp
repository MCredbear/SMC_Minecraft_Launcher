#include "downloader.h"

Downloader::Downloader(QObject *parent)
    : QObject{parent}
{
}

Thread::Thread(Downloader *parent, const File *file)
{
    this->setParent(parent);
    this->file = file;
    connect(this, &Thread::threadCompleted, parent, &Downloader::onThreadCompleted);
    connect(this, &Thread::threadFailed, parent, &Downloader::onThreadFailed);
    connect(parent, &Downloader::stopped, this, &QThread::quit);
    connect(this, &Thread::finished, this, &Thread::deleteLater);
}

void Thread::run()
{
    QNetworkAccessManager manager;
    QNetworkRequest request(file->url);
    QEventLoop eventLoop;
    QNetworkReply *reply = manager.get(request);
    connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();
    if (reply->error() == QNetworkReply::NoError)
    {
        QFile downloadedFile(file->path);
        QFileInfo downloadedFileInfo(downloadedFile);
        QDir dir;
        if (dir.mkpath(downloadedFileInfo.path()))
        {
            if (downloadedFile.open(QIODevice::WriteOnly))
            {
                downloadedFile.write(reply->readAll());
                downloadedFile.close();
                if (AssetChecker::checkFile(file->path, file->sha1) == File::fine){
                    emit threadCompleted();
                }
                    
                else
                {
                    if (retryCount != 5)
                    {
                        retryCount++;
                        run();
                    }
                    else
                        emit threadFailed();
                }
            }
            else
                emit threadFailed();
        }
        else
            emit threadFailed();
    }
    else
    {
        if (retryCount != 5)
        {
            retryCount++;
            run();
        }
        else
            emit threadFailed();
    }
}

void Downloader::onThreadCompleted()
{
    setProgress(progress + 1);
    if (progress <= total - threads)
    {
        Thread *thread = new Thread(this, &downloadList->at(progress + threads - 1));
        thread->start();
    }
    if (progress == total)
    {
        status = completed;
        emit stopped();
    }
}

void Downloader::onThreadFailed()
{
    status = faild;
    emit stopped();
}

int Downloader::startDownload(QList<File> *downloadList)
{
    this->downloadList = downloadList;
    setTotal(downloadList->length());
    if (total > 0)
    {
        status = progressing;
        QEventLoop eventLoop;
        connect(this, &Downloader::stopped, &eventLoop, &QEventLoop::quit);
        for (int i = 0; i < std::min(threads, total); i++)
        {
            if (status = progressing)
            {
                Thread *thread = new Thread(this, &downloadList->at(i));
                thread->start();
            }
            else
                return status;
        }
        eventLoop.exec();
    }
    else
        status = completed;

    return status;
}

int Downloader::getThreads()
{
    return threads;
}

void Downloader::setThreads(int threads)
{
    this->threads = threads;
    emit threadsChanged();
}

int Downloader::getProgress()
{
    return progress;
}

void Downloader::setProgress(int progress)
{
    this->progress = progress;
    emit progressChanged();
}

int Downloader::getTotal()
{
    return total;
}

void Downloader::setTotal(int total)
{
    this->total = total;
    emit totalChanged();
}