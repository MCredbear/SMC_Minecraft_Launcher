#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>

class downloader : public QObject
{
    Q_OBJECT
public:
    explicit downloader(QObject *parent = nullptr);

signals:

};

#endif // DOWNLOADER_H
