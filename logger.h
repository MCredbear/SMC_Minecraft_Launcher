#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>

class Logger : public QObject
{
    Q_OBJECT
public:
    explicit Logger(QObject *parent = nullptr);

    Q_INVOKABLE QByteArray loginMojang(QString username, QString password);

// 由于我办不了VESA卡，注册不了微软的Azure服务，所以没法用xbox登录
//    Q_INVOKABLE QByteArray loginXbox(QString username, QString password);

signals:

};

#endif // LOGGER_H
