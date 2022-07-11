#include "logger.h"

Logger::Logger(QObject *parent)
    : QObject{parent}
{
}

QByteArray Logger::loginMojang(QString username, QString password)
{
    QNetworkAccessManager manager;
    QEventLoop eventLoop;
    QNetworkRequest request(QUrl("https://authserver.mojang.com/authenticate"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray requestData = "{\"agent\":{\"name\":\"Minecraft\",\"version\":1},\"username\":\"" + username.toUtf8() + "\",\"password\":\"" + password.toUtf8() + "\"}";
    // {
    //    "agent": {
    //        "name": "Minecraft",                // 默认为Minecraft，可选
    //        "version": 1                        // 未来可能会改（不会）
    //    },
    //    "username": "mojang用户名",              // 可以是邮箱地址或旧版mojang用户名
    //    "password": "密码",
    //    "clientToken": "客户端标识符",            // 可选的，用于复用该值
    // }

    QNetworkReply *reply = manager.post(request, requestData);
    connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();
    qDebug() << reply->readAll();
}

// 由于我办不了VESA卡，注册不了微软的Azure服务，所以没法用xbox登录
// QByteArray Logger::loginXbox(QString username, QString password)
// {
//     QNetworkAccessManager manager;
//     QEventLoop eventLoop;
//     QNetworkRequest request(QUrl("https://user.auth.xboxlive.com/user/authenticate"));
//     request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
//     QByteArray requestData = "{\"agent\":{\"name\":\"Minecraft\",\"version\":1},\"username\":\"" + username.toUtf8() + "\",\"password\":\"" + password.toUtf8() + "\"}";
//     // {
//     //     "Properties": {
//     //         "AuthMethod": "RPS",
//     //         "SiteName": "user.auth.xboxlive.com",
//     //         "RpsTicket": "d=%1"
//     //     },
//     //     "RelyingParty": "http://auth.xboxlive.com",
//     //     "TokenType": "JWT"
//     // }

//     QNetworkReply *reply = manager.post(request, requestData);
//     connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
//     eventLoop.exec();
//     qDebug() << reply->readAll();
// }
